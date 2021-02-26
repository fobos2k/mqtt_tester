#!/usr/bin/env bash

RAPIDJSON_VERSION=1.1.0

## APP parameters
export APP_NAME=mqtt_tester
export TEST_APP_NAME=test_${APP_NAME}
export APP_ROOT_PATH=$(dirname $(realpath $0))
export APP_BUILD_PATH=${APP_ROOT_PATH}/_build
export APP_TEMP_PATH=${APP_ROOT_PATH}/_temp
export APP_LOGS_PATH=${APP_TEMP_PATH}/logs
export APP_REPORTS_PATH=${APP_TEMP_PATH}/reports
export APP_COVERAGE_PATH=${APP_TEMP_PATH}/coverage

mkdir -pv ${APP_BUILD_PATH}
mkdir -pv ${APP_LOGS_PATH}
mkdir -pv ${APP_REPORTS_PATH}
mkdir -pv ${APP_COVERAGE_PATH}

## Isolator++
# ISOLATOR_PATH=${_3RD_TOOLS}/isolator++
export ISOLATOR_INCLUDE_PATH=/usr/include/typemock
export ISOLATOR_LIB_PATH=/usr/lib64/typemock
export LD_BIND_NOW=1

## RapidJson
## ex. rapidjson-1.1.0
RAPIDJSON_FOLDER=rapidjson-${RAPIDJSON_VERSION}
export RAPIDJSON_PATH=${_3RD_TOOLS}/${RAPIDJSON_FOLDER}

export LD_LIBRARY_PATH=${ISOLATOR_LIB_PATH}:${APP_TEMP_PATH}/lib
export PATH=${APP_TEMP_PATH}/bin:${PATH}
