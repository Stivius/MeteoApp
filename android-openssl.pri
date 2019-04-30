# includes openssl libs onto android build
android {
  ANDROID_EXTRA_LIBS += $$PWD/prebuilt/libcrypto.so
  ANDROID_EXTRA_LIBS += $$PWD/prebuilt/libssl.so
}
