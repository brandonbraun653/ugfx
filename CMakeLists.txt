# This file should have a target for:
#   Drivers -> Any necessary LCD drivers
#   Source  -> Single library per folder
#   Include -> One target for all includes

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
add_library(ugfx_gadc_lib STATIC ${UGFX_SRC_DIR}/gadc/gadc.c)
target_link_libraries(ugfx_gadc_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gadc_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gadc_lib.cmake")

# ===============================================
# gaudio
# ===============================================
add_library(ugfx_gaudio_lib STATIC ${UGFX_SRC_DIR}/gaudio/gaudio.c)
target_link_libraries(ugfx_gaudio_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gaudio_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gaudio_lib.cmake")

# ===============================================
# gdisp
# ===============================================
add_library(ugfx_gdisp_lib STATIC
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
target_link_libraries(ugfx_gdisp_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gdisp_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gdisp_lib.cmake")

# ===============================================
# gdriver
# ===============================================
add_library(ugfx_gdriver_lib STATIC ${UGFX_SRC_DIR}/gdriver/gdriver.c)
target_link_libraries(ugfx_gdriver_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gdriver_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gdriver_lib.cmake")

# ===============================================
# gevent
# ===============================================
add_library(ugfx_gevent_lib STATIC ${UGFX_SRC_DIR}/gevent/gevent.c)
target_link_libraries(ugfx_gevent_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gevent_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gevent_lib.cmake")

# ===============================================
# gfile
# ===============================================
add_library(ugfx_gfile_lib STATIC
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
target_link_libraries(ugfx_gfile_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gfile_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gfile_lib.cmake")

# ===============================================
# ginput
# ===============================================
add_library(ugfx_ginput_lib STATIC
  ${UGFX_SRC_DIR}/ginput/ginput.c
  ${UGFX_SRC_DIR}/ginput/ginput_mouse.c
  ${UGFX_SRC_DIR}/ginput/ginput_keyboard.c
  ${UGFX_SRC_DIR}/ginput/ginput_keyboard_microcode.c
  ${UGFX_SRC_DIR}/ginput/ginput_toggle.c
  ${UGFX_SRC_DIR}/ginput/ginput_dial.c
)
target_link_libraries(ugfx_ginput_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_ginput_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_ginput_lib.cmake")


# ===============================================
# gmisc
# ===============================================
add_library(ugfx_gmisc_lib STATIC
  ${UGFX_SRC_DIR}/gmisc/gmisc.c
  ${UGFX_SRC_DIR}/gmisc/gmisc_arrayops.c
  ${UGFX_SRC_DIR}/gmisc/gmisc_matrix2d.c
  ${UGFX_SRC_DIR}/gmisc/gmisc_trig.c
  ${UGFX_SRC_DIR}/gmisc/gmisc_hittest.c
)
target_link_libraries(ugfx_gmisc_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gmisc_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gmisc_lib.cmake")

# ===============================================
# gos
# ===============================================
add_library(ugfx_gos_lib STATIC
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
target_link_libraries(ugfx_gos_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gos_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gos_lib.cmake")

# ===============================================
# gqueue
# ===============================================
add_library(ugfx_gqueue_lib STATIC ${UGFX_SRC_DIR}/gqueue/gqueue.c)
target_link_libraries(ugfx_gqueue_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gqueue_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gqueue_lib.cmake")

# ===============================================
# gtimer
# ===============================================
add_library(ugfx_gtimer_lib STATIC ${UGFX_SRC_DIR}/gtimer/gtimer.c)
target_link_libraries(ugfx_gtimer_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gtimer_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gtimer_lib.cmake")

# ===============================================
# gwin
# ===============================================
add_library(ugfx_gwin_lib STATIC
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
target_link_libraries(ugfx_gwin_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gwin_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gwin_lib.cmake")

# ===============================================
# gcore
# ===============================================
add_library(ugfx_gcore_lib STATIC ${UGFX_SRC_DIR}/gfx.c)
target_link_libraries(ugfx_gcore_lib PRIVATE ugfx_inc prj_device_target prj_build_target)
export(TARGETS ugfx_gcore_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_gcore_lib.cmake")

# ===============================================
# All source libs
# ===============================================
add_library(ugfx_lib INTERFACE)
target_link_libraries(ugfx_lib INTERFACE
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
export(TARGETS ugfx_lib FILE "${PROJECT_BINARY_DIR}/ugfx/ugfx_lib.cmake")

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
add_library(ugfx_st7735_lib STATIC ${UGFX_VER_DIR}/drivers/gdisp/ST7735/gdisp_lld_ST7735.c)
target_link_libraries(ugfx_st7735_lib PRIVATE
  root_inc
  ugfx_inc
  ugfx_st7735_inc
  prj_device_target
  prj_build_target
)
export(TARGETS ugfx_st7735_lib FILE "${PROJECT_BINARY_DIR}/ugfx/drivers/ugfx_st7735_lib.cmake")
