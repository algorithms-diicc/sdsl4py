IF(NOT EXISTS "/home/gasparubuntu/Escritorio/PROYECTO COMPUTACIONAL/opcion1sa/sdsl4py/build/temp.linux-x86_64-cpython-312/sdsl4py/sdsl-lite/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/home/gasparubuntu/Escritorio/PROYECTO COMPUTACIONAL/opcion1sa/sdsl4py/build/temp.linux-x86_64-cpython-312/sdsl4py/sdsl-lite/install_manifest.txt\"")
ENDIF(NOT EXISTS "/home/gasparubuntu/Escritorio/PROYECTO COMPUTACIONAL/opcion1sa/sdsl4py/build/temp.linux-x86_64-cpython-312/sdsl4py/sdsl-lite/install_manifest.txt")

FILE(READ "/home/gasparubuntu/Escritorio/PROYECTO COMPUTACIONAL/opcion1sa/sdsl4py/build/temp.linux-x86_64-cpython-312/sdsl4py/sdsl-lite/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")

SET(NUM 0)
FOREACH(file ${files})
  IF(EXISTS "$ENV{DESTDIR}${file}")
    MESSAGE(STATUS "Looking for \"$ENV{DESTDIR}${file}\" - found")
    SET(UNINSTALL_CHECK_${NUM} 1)
  ELSE(EXISTS "$ENV{DESTDIR}${file}")
    MESSAGE(STATUS "Looking for \"$ENV{DESTDIR}${file}\" - not found")
    SET(UNINSTALL_CHECK_${NUM} 0)
  ENDIF(EXISTS "$ENV{DESTDIR}${file}")
  MATH(EXPR NUM "1 + ${NUM}")
ENDFOREACH(file)

SET(NUM 0)
FOREACH(file ${files})
  IF(${UNINSTALL_CHECK_${NUM}})
    MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    EXEC_PROGRAM(
      "/tmp/pip-build-env-rn_0gc3j/overlay/lib/python3.12/site-packages/cmake/data/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    IF(NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    ENDIF(NOT "${rm_retval}" STREQUAL 0)
  ENDIF(${UNINSTALL_CHECK_${NUM}})
  MATH(EXPR NUM "1 + ${NUM}")
ENDFOREACH(file)

FILE(REMOVE "/home/gasparubuntu/Escritorio/PROYECTO COMPUTACIONAL/opcion1sa/sdsl4py/build/temp.linux-x86_64-cpython-312/sdsl4py/sdsl-lite/install_manifest.txt")
