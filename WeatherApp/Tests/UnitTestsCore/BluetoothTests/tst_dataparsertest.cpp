#include <QtTest>
#include <memory>
#include "../../../WeatherPrototype/bluetooth/model/ChunkedDataParser.hpp"
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
    void testCreateDataParser();
private:

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
    QCOMPARE(1,1);
}

void DataParserTest::cleanupTestCase()
{

}

void DataParserTest::testCreateDataParser()
{

}

QTEST_APPLESS_MAIN(DataParserTest)

#include "tst_dataparsertest.moc"
