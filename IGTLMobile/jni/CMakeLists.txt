include_directories(
  "${ANDROID_NDK}/platforms/android-19/arch-arm/usr/include"
  "${OpenIGTLink_INCLUDES}"
  "${ANDROID_NDK}/sources/android/native_app_glue/"
)

set(sources
  main.cxx
  myUtils.h
  igtlClient.h
  igtlServer.h
  ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c
)

add_library(IGTLMobile SHARED ${sources})
target_link_libraries(IGTLMobile
  android
  log
  ${OpenIGTLink_LIBRARY}

)

