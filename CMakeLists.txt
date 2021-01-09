include("${COMMON_TOOL_ROOT}/cmake/utility/embedded.cmake")

# =============================================================================
# Constants
# =============================================================================
set(UGFX_VER_DIR "./ugfx_2.9")
set(UGFX_SRC_DIR "./ugfx_2.9/src")

# =============================================================================
# Include Targets
# =============================================================================
# Include directory to gfx.h
add_library(root_inc INTERFACE)
target_include_directories(root_inc INTERFACE ${UGFX_VER_DIR})
export(TARGETS root_inc FILE "${PROJECT_BINARY_DIR}/ugfx/root_inc.cmake")

# Helper function to generate exported targets for the various driver modules
function(generate_include_target driver)
  add_library(${driver}_inc INTERFACE)
  target_include_directories(${driver}_inc INTERFACE ${UGFX_SRC_DIR}/${driver})
  export(TARGETS ${driver}_inc FILE "${PROJECT_BINARY_DIR}/ugfx/${driver}_inc.cmake")
endfunction()

generate_include_target(gadc)
generate_include_target(gaudio)
generate_include_target(gdisp)
generate_include_target(gdriver)
generate_include_target(gevent)
generate_include_target(gfile)
generate_include_target(ginput)
generate_include_target(gmisc)
generate_include_target(gos)
generate_include_target(gqueue)
generate_include_target(gtimer)
generate_include_target(gwin)

# Interface to include all directories
add_library(ugfx_inc INTERFACE)
target_link_libraries(ugfx_inc INTERFACE
  gadc_inc
  gaudio_inc
  gdisp_inc
  gdriver_inc
  gevent_inc
  gfile_inc
  ginput_inc
  gmisc_inc
  gos_inc
  gqueue_inc
  gtimer_inc
  gwin_inc
  project_ugfx_inc   # Must be supplied by the project to inject gfxconf.h
  root_inc
)
export(TARGETS ugfx_inc FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_inc.cmake")


# =============================================================================
# Source Libraries
# =============================================================================
# ===============================================
# gadc
# ===============================================
function(build_library_adc variant)
  set(LIB ugfx_gadc_lib${variant})
  add_library(${LIB} STATIC ${UGFX_SRC_DIR}/gadc/gadc.c)
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_adc)

# ===============================================
# gaudio
# ===============================================
function(build_library_gaudio variant)
  set(LIB ugfx_gaudio_lib${variant})
  add_library(${LIB} STATIC ${UGFX_SRC_DIR}/gaudio/gaudio.c)
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gaudio)

# ===============================================
# gdisp
# ===============================================
function(build_library_gdisp variant)
  set(LIB ugfx_gdisp_lib${variant})
  add_library(${LIB} STATIC
    ${UGFX_SRC_DIR}/gdisp/gdisp.c
    ${UGFX_SRC_DIR}/gdisp/gdisp.c
    ${UGFX_SRC_DIR}/gdisp/gdisp_fonts.c
    ${UGFX_SRC_DIR}/gdisp/gdisp_pixmap.c
    ${UGFX_SRC_DIR}/gdisp/gdisp_image.c
    ${UGFX_SRC_DIR}/gdisp/gdisp_image_native.c
    ${UGFX_SRC_DIR}/gdisp/gdisp_image_gif.c
    ${UGFX_SRC_DIR}/gdisp/gdisp_image_bmp.c
    ${UGFX_SRC_DIR}/gdisp/gdisp_image_jpg.c
    ${UGFX_SRC_DIR}/gdisp/gdisp_image_png.c
  )
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gdisp)

# ===============================================
# gdriver
# ===============================================
function(build_library_gdriver variant)
  set(LIB ugfx_gdriver_lib${variant})
  add_library(${LIB} STATIC ${UGFX_SRC_DIR}/gdriver/gdriver.c)
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gdriver)

# ===============================================
# gevent
# ===============================================
function(build_library_gevent variant)
  set(LIB ugfx_gevent_lib${variant})
  add_library(${LIB} STATIC ${UGFX_SRC_DIR}/gevent/gevent.c)
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gevent)

# ===============================================
# gfile
# ===============================================
function(build_library_gfile variant)
  set(LIB ugfx_gfile_lib${variant})
  add_library(${LIB} STATIC
    ${UGFX_SRC_DIR}/gfile/gfile.c
    ${UGFX_SRC_DIR}/gfile/gfile_fs_native.c
    ${UGFX_SRC_DIR}/gfile/gfile_fs_ram.c
    ${UGFX_SRC_DIR}/gfile/gfile_fs_rom.c
    ${UGFX_SRC_DIR}/gfile/gfile_fs_fatfs.c
    ${UGFX_SRC_DIR}/gfile/gfile_fs_petitfs.c
    ${UGFX_SRC_DIR}/gfile/gfile_fs_mem.c
    ${UGFX_SRC_DIR}/gfile/gfile_fs_chibios.c
    ${UGFX_SRC_DIR}/gfile/gfile_fs_strings.c
    ${UGFX_SRC_DIR}/gfile/gfile_printg.c
    ${UGFX_SRC_DIR}/gfile/gfile_scang.c
    ${UGFX_SRC_DIR}/gfile/gfile_stdio.c
    ${UGFX_SRC_DIR}/gfile/gfile_fatfs_wrapper.c
    ${UGFX_SRC_DIR}/gfile/gfile_fatfs_diskio_chibios.c
    ${UGFX_SRC_DIR}/gfile/gfile_petitfs_wrapper.c
    ${UGFX_SRC_DIR}/gfile/gfile_petitfs_diskio_chibios.c
  )
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gfile)

# ===============================================
# ginput
# ===============================================
function(build_library_ginput variant)
  set(LIB ugfx_ginput_lib${variant})
  add_library(${LIB} STATIC
    ${UGFX_SRC_DIR}/ginput/ginput.c
    ${UGFX_SRC_DIR}/ginput/ginput_mouse.c
    ${UGFX_SRC_DIR}/ginput/ginput_keyboard.c
    ${UGFX_SRC_DIR}/ginput/ginput_keyboard_microcode.c
    ${UGFX_SRC_DIR}/ginput/ginput_toggle.c
    ${UGFX_SRC_DIR}/ginput/ginput_dial.c
  )
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_ginput)


# ===============================================
# gmisc
# ===============================================
function(build_library_gmisc variant)
  set(LIB ugfx_gmisc_lib${variant})
  add_library(${LIB} STATIC
    ${UGFX_SRC_DIR}/gmisc/gmisc.c
    ${UGFX_SRC_DIR}/gmisc/gmisc_arrayops.c
    ${UGFX_SRC_DIR}/gmisc/gmisc_matrix2d.c
    ${UGFX_SRC_DIR}/gmisc/gmisc_trig.c
    ${UGFX_SRC_DIR}/gmisc/gmisc_hittest.c
  )
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gmisc)

# ===============================================
# gos
# ===============================================
function(build_library_gos variant)
  set(LIB ugfx_gos_lib${variant})
  add_library(${LIB} STATIC
    ${UGFX_SRC_DIR}/gos/gos_chibios.c
    ${UGFX_SRC_DIR}/gos/gos_freertos.c
    ${UGFX_SRC_DIR}/gos/gos_win32.c
    ${UGFX_SRC_DIR}/gos/gos_linux.c
    ${UGFX_SRC_DIR}/gos/gos_osx.c
    ${UGFX_SRC_DIR}/gos/gos_raw32.c
    ${UGFX_SRC_DIR}/gos/gos_ecos.c
    ${UGFX_SRC_DIR}/gos/gos_rawrtos.c
    ${UGFX_SRC_DIR}/gos/gos_arduino.c
    ${UGFX_SRC_DIR}/gos/gos_cmsis.c
    ${UGFX_SRC_DIR}/gos/gos_nios.c
    ${UGFX_SRC_DIR}/gos/gos_zephyr.c
    ${UGFX_SRC_DIR}/gos/gos_x_threads.c
    ${UGFX_SRC_DIR}/gos/gos_x_heap.c
  )
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gos)

# ===============================================
# gqueue
# ===============================================

function(build_library_gqueue variant)
  set(LIB ugfx_gqueue_lib${variant})
  add_library(${LIB} STATIC ${UGFX_SRC_DIR}/gqueue/gqueue.c)
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gqueue)

# ===============================================
# gtimer
# ===============================================
function(build_library_gtimer variant)
  set(LIB ugfx_gtimer_lib${variant})
  add_library(${LIB} STATIC ${UGFX_SRC_DIR}/gtimer/gtimer.c)
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gtimer)

# ===============================================
# gwin
# ===============================================
function(build_library_gwin variant)
  set(LIB ugfx_gwin_lib${variant})
  add_library(${LIB} STATIC
    ${UGFX_SRC_DIR}/gwin/gwin.c
    ${UGFX_SRC_DIR}/gwin/gwin_widget.c
    ${UGFX_SRC_DIR}/gwin/gwin_wm.c
    ${UGFX_SRC_DIR}/gwin/gwin_console.c
    ${UGFX_SRC_DIR}/gwin/gwin_graph.c
    ${UGFX_SRC_DIR}/gwin/gwin_button.c
    ${UGFX_SRC_DIR}/gwin/gwin_slider.c
    ${UGFX_SRC_DIR}/gwin/gwin_checkbox.c
    ${UGFX_SRC_DIR}/gwin/gwin_image.c
    ${UGFX_SRC_DIR}/gwin/gwin_label.c
    ${UGFX_SRC_DIR}/gwin/gwin_radio.c
    ${UGFX_SRC_DIR}/gwin/gwin_list.c
    ${UGFX_SRC_DIR}/gwin/gwin_progressbar.c
    ${UGFX_SRC_DIR}/gwin/gwin_container.c
    ${UGFX_SRC_DIR}/gwin/gwin_frame.c
    ${UGFX_SRC_DIR}/gwin/gwin_tabset.c
    ${UGFX_SRC_DIR}/gwin/gwin_gl3d.c
    ${UGFX_SRC_DIR}/gwin/gwin_keyboard.c
    ${UGFX_SRC_DIR}/gwin/gwin_keyboard_layout.c
    ${UGFX_SRC_DIR}/gwin/gwin_textedit.c
  )
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gwin)

# ===============================================
# gcore
# ===============================================
function(build_library_gcore variant)
  set(LIB ugfx_gcore_lib${variant})
  add_library(${LIB} STATIC ${UGFX_SRC_DIR}/gfx.c)
  target_link_libraries(${LIB}  PRIVATE ugfx_inc prj_device_target prj_build_target${variant})
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gcore)

# ====================================================
# All source libs
# ====================================================
set(all_libraries
  ugfx_gadc_lib
  ugfx_gaudio_lib
  ugfx_gdisp_lib
  ugfx_gdriver_lib
  ugfx_gevent_lib
  ugfx_gfile_lib
  ugfx_ginput_lib
  ugfx_gmisc_lib
  ugfx_gos_lib
  ugfx_gqueue_lib
  ugfx_gtimer_lib
  ugfx_gwin_lib
  ugfx_gcore_lib
)

# ====================================================
# This function generates the following targets:
#   ugfx_lib
#   ugfx_lib_rel
#   ugfx_lib_rel_dbg
#   ugfx_lib_dbg
#
# Each target builds the appropriate variant of the
# libraries listed above in "all_libraries".
# ====================================================
function(build_ugfx_core variant)

  # Add the variant flag to each library target
  set(all_libraries_tmp${variant} "")
  foreach(lib ${all_libraries})
    list(APPEND all_libraries_tmp${variant} ${lib}${variant})
  endforeach()

  # Create interface library for the appropriate variant
  set(UGFX_CORE${variant} ugfx_lib${variant})
  add_library("${UGFX_CORE${variant}}" INTERFACE)
  target_link_libraries("${UGFX_CORE${variant}}" INTERFACE "${all_libraries_tmp${variant}}")
  export(TARGETS "${UGFX_CORE${variant}}" FILE "${PROJECT_BINARY_DIR}/ugfx/${UGFX_CORE${variant}}.cmake")

endfunction()
add_target_variants(build_ugfx_core)

# =============================================================================
# Driver Libraries
# =============================================================================
# ===============================================
# ST7735
# ===============================================
# Include target
add_library(ugfx_st7735_inc INTERFACE)
target_include_directories(ugfx_st7735_inc INTERFACE ${UGFX_VER_DIR}/drivers/gdisp/ST7735)
export(TARGETS ugfx_st7735_inc FILE "${PROJECT_BINARY_DIR}/ugfx/drivers/ugfx_st7735_inc.cmake")

# Library target

function(build_library_gst7735 variant)
  set(LIB ugfx_st7735_lib${variant})
  add_library(${LIB} STATIC ${UGFX_VER_DIR}/drivers/gdisp/ST7735/gdisp_lld_ST7735.c)
  target_link_libraries(${LIB}  PRIVATE
    root_inc
    ugfx_inc
    ugfx_st7735_inc
    prj_device_target
    prj_build_target${variant}
  )
  export(TARGETS ${LIB} FILE "${PROJECT_BINARY_DIR}/ugfx/drivers/${LIB}.cmake")
endfunction()

add_target_variants(build_library_gst7735)
