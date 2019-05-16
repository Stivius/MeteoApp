#include <QtTest>
#include <memory>
#include "../../../WeatherPrototype/bluetooth/model/ChunkedDataParser.hpp"
#include "../../../WeatherPrototype/bluetooth/model/BadPacketException.hpp"
// add necessary includes here

class DataParserTest : public QObject
{
    Q_OBJECT

public:
    DataParserTest();
    ~DataParserTest();

private slots:

    void initTestCase();
    void cleanupTestCase();

    void testParsePositiveTemperature();
    void testParseNegativeTemperature();
    void testParseMinHumidity();
    void testParseMaxHumidity();
    void testParsePressure();

    void testComplexParse();

    void expectedInvalidStringWithOnlyNumbers();
    void expectedInvalidStringWithOnlyLetters();

private:

    static constexpr int ExpectedPositiveTemperature = 20;
    static constexpr int ExpectedNegativeTemperature = -20;
    static constexpr int ExpectedMinHumidity = 0;
    static constexpr int ExpectedMaxHumidity = 100;
    static constexpr int ExpectedPressure = 1000;

   std::unique_ptr<IReceivedDataParser> m_testedParser;
};

DataParserTest::DataParserTest()
{

}

DataParserTest::~DataParserTest()
{

}

void DataParserTest::initTestCase()
{
    m_testedParser = std::make_unique<ChunkedDataParser>();
}

void DataParserTest::cleanupTestCase()
{

}

void DataParserTest::testParsePositiveTemperature()
{

    m_testedParser->tryParseValue("temp:20");

    QCOMPARE( ExpectedPositiveTemperature , m_testedParser->getTemperature() );
}

void DataParserTest::testParseNegativeTemperature()
{

    m_testedParser->tryParseValue("temp:-20");

    QCOMPARE( ExpectedNegativeTemperature , m_testedParser->getTemperature() );
}

void DataParserTest::testParseMinHumidity()
{

    m_testedParser->tryParseValue("hum:0");

    QCOMPARE( ExpectedMinHumidity , m_testedParser->getHumidity() );
}


void DataParserTest::testParseMaxHumidity()
{

    m_testedParser->tryParseValue("hum:100");

    QCOMPARE( ExpectedMaxHumidity , m_testedParser->getHumidity() );
}

void DataParserTest::testParsePressure()
{
    m_testedParser->tryParseValue("pressure:1000");
    QCOMPARE( ExpectedPressure , m_testedParser->getPressure() );
}

void DataParserTest::testComplexParse()
{
    m_testedParser->tryParseValue("hum:100");
    m_testedParser->tryParseValue("temp:-20");
    m_testedParser->tryParseValue("pressure:1000");

    QCOMPARE( ExpectedPressure , m_testedParser->getPressure() );
    QCOMPARE( ExpectedMaxHumidity , m_testedParser->getHumidity() );
    QCOMPARE( ExpectedNegativeTemperature , m_testedParser->getTemperature() );
}

void DataParserTest::expectedInvalidStringWithOnlyNumbers()
{
    QVERIFY_EXCEPTION_THROWN( m_testedParser->tryParseValue("111111"), BadPacketException );
}

void DataParserTest::expectedInvalidStringWithOnlyLetters()
{
    QVERIFY_EXCEPTION_THROWN( m_testedParser->tryParseValue("testbad"), BadPacketException );
}

QTEST_APPLESS_MAIN(DataParserTest)

#include "tst_dataparsertest.moc"
