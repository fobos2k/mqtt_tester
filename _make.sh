#!/bin/bash

help_usage()
{
    echo "$0 [<options>]"
    exit 0
}

debug_print_variables()
{
    echo "======> Envirovnment (enabled debug output)..."
    echo -e "\t CLEAN_BUILD = ${CLEAN_BUILD}"
    echo -e "\t EXECUTE_BUILD = ${EXECUTE_BUILD}"
    echo -e "\t EXECUTE_TESTS = ${EXECUTE_TESTS}"
    echo -e "\t EXECUTE_COVERAGE = ${EXECUTE_COVERAGE}"
    echo -e "\t VERBOSE = ${VERBOSE}"
}

get_coverage()
{
    cd ${APP_ROOT_PATH}
    echo "======> Writing coverage report (${TEST_APP_NAME}.html)..."
    GCOVR_CMD="gcovr"
    GCOVR_CMD+=" --output ${APP_COVERAGE_PATH}/${TEST_APP_NAME}.html"
    GCOVR_CMD+=" --html"
    GCOVR_CMD+=" --html-details"
    GCOVR_CMD+=" --exclude-unreachable-branches"
    GCOVR_CMD+=" --delete"
    [ ${VERBOSE} ] && echo "${GCOVR_CMD}"
    eval ${GCOVR_CMD}
}

run_tests()
{
    cd ${APP_ROOT_PATH}
    echo "======> Testing: ${TEST_APP_NAME} ..."
    TEST_REPORT=${APP_REPORTS_PATH}/${TEST_APP_NAME}
    TEST_CMD="${TEST_APP_NAME} --build_info=true"
    TEST_CMD+=" --color_output"
    TEST_CMD+=" --detect_memory_leaks"
    TEST_CMD+=" --log_level=message"
#    TEST_CMD+=" --log_sink=${TEST_REPORT}.log"
    TEST_CMD+=" --report_level=detailed"
#    TEST_CMD+=" --report_sink=${TEST_REPORT}.txt"
#    TEST_CMD+=" --report_memory_leaks_to=${TEST_REPORT}_memory_leaks.txt"
    [ ${VERBOSE} ] && echo "${TEST_CMD}"
    eval ${TEST_CMD}
}

cmake_config()
{
    echo "======> Clean and configure build: ${TEST_APP_NAME} ..."
    rm -rf ${APP_BUILD_PATH}
    mkdir -p ${APP_BUILD_PATH}

    cd ${APP_BUILD_PATH}
    cmake ..
}

cmake_build()
{
    # echo "======> Build: ${TEST_APP_NAME} ..."
    # ./_update_includes.sh

    cd ${APP_BUILD_PATH}
    cmake --build .                                     \
        && cmake --install . --prefix ${APP_TEMP_PATH}
}

main()
{
    if [ -z ${_3RD_TOOLS} ]; then
        echo "ERROR! Please set the _3RD_TOOLS variable."
        echo "Example:"
        echo -e "\texport _3RD_TOOLS=${HOME}/_develop/_3rdparty"
        exit 1
    fi

    . ./env.sh

    CLEAN_BUILD=
    EXECUTE_BUILD=1
    EXECUTE_TESTS=1
    EXECUTE_COVERAGE=1
    VERBOSE=

    while [ -n $1 ]; do
        PARAM=`echo $1 | awk -F= '{print $1}'`
        VALUE=`echo $1 | awk -F= '{print $2}'`

        case ${PARAM} in
            -h | --help)
                help_usage
                exit
                ;;
            -c | --clean)
                CLEAN_BUILD=1
                ;;
            -t | --test)
                TEST_APP_NAME=${VALUE}
                ;;
            --no-build)
                EXECUTE_BUILD=
                ;;
            --no-tests)
                EXECUTE_TESTS=
                EXECUTE_COVERAGE=
                ;;
            --no-coverage)
                EXECUTE_COVERAGE=
                ;;
            -v | --verbose)
                VERBOSE=1
                ;;
            *)
                # help_usage
                break
                ;;
        esac
        shift
    done

    [ ${VERBOSE} ] && debug_print_variables

    if [ ${CLEAN_BUILD} ]; then
        cmake_config
        [ $? -ne 0 ] && exit 1
    fi

    if [ ${EXECUTE_BUILD} ]; then
        cmake_build
        [ $? -ne 0 ] && exit 1
    fi

    if [ ${EXECUTE_TESTS} ]; then
        echo "====> run_tests"
        run_tests
        # [ $? -ne 0 ] && exit 1
    fi

    if [ ${EXECUTE_COVERAGE} ]; then
        echo "====> get_coverage"
        get_coverage
        # [ $? -ne 0 ] && exit 1
    fi
}

main $@
