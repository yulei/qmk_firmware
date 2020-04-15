
@rem launch the cmsis configuration tools

@if [%1]==[] (
    @set wizard=..\..\..\lib\nRF5_SDK_16.0.0_98a08e2\external_tools\cmsisconfig\CMSIS_Configuration_Wizard.jar
) else (
    @set wizard=%1
)

@if [%2]==[] (
    @set config=sdk_config.h
) else (
    @set config=%2
)

java -jar %wizard% %config%
