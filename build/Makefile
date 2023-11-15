PROJECT_NAME     := BrjnkNrf51822Proj
TARGETS          := nrf51822_xxaa

ifeq ($(PARAM_SOFTDEVICE), S130)
	ifeq ($(PARAM_VARIANT), DEBUG)
		OUTPUT_DIRECTORY := output/debugS130
		LINKER_SCRIPT := gcc_nrf51_S130.ld
	else ifeq ($(PARAM_VARIANT), RELEASE_PROD)
		OUTPUT_DIRECTORY := output/releaseProdS130
		LINKER_SCRIPT := gcc_nrf51_S130.ld
	else
		OUTPUT_DIRECTORY := output/releaseS130
		LINKER_SCRIPT := gcc_nrf51_S130.ld
	endif
else
	ifeq ($(PARAM_VARIANT), DEBUG)
		OUTPUT_DIRECTORY := output/debug
		LINKER_SCRIPT := gcc_nrf51.ld
	else ifeq ($(PARAM_VARIANT), RELEASE_PROD)
		OUTPUT_DIRECTORY := output/releaseProd
		LINKER_SCRIPT := gcc_nrf51.ld
	else
		OUTPUT_DIRECTORY := output/release
		LINKER_SCRIPT := gcc_nrf51.ld
	endif
endif

$(shell mkdir -p $(OUTPUT_DIRECTORY))

SDK_ROOT := /opt/nRF5_SDK_12.3.0_d7731ad/
PROJ_DIR := ..

# Source files common to all targets
SRC_FILES +=
SRC_FILES += $(PROJ_DIR)/main.cpp
SRC_FILES += $(PROJ_DIR)/BleAdvertiser.cpp
SRC_FILES += $(PROJ_DIR)/DS18B20.cpp
SRC_FILES += $(PROJ_DIR)/OneWire.cpp
SRC_FILES += $(PROJ_DIR)/SupplyBranch.cpp
SRC_FILES += $(PROJ_DIR)/SwUart.cpp
SRC_FILES += $(PROJ_DIR)/TimeslotManager.cpp
SRC_FILES += $(PROJ_DIR)/StatusLedDriver.cpp
SRC_FILES +=
SRC_FILES +=
SRC_FILES +=  $(SDK_ROOT)/components/toolchain/gcc/gcc_startup_nrf51.S \
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_channel_config/ant_channel_config.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_encryption/ant_encrypt_config.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_encryption/ant_encrypt_negotiation_slave.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_fs/antfs.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_fs/crc.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_key_manager/ant_key_manager.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/pages/ant_bpwr_common_data.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/pages/ant_bpwr_page_1.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/pages/ant_bpwr_page_16.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/pages/ant_bpwr_page_17.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/pages/ant_bpwr_page_18.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/pages/ant_bpwr_page_torque.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/simulator/ant_bpwr_simulator.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/ant_bpwr.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/pages/ant_bsc_combined_page_0.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/pages/ant_bsc_page_0.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/pages/ant_bsc_page_1.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/pages/ant_bsc_page_2.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/pages/ant_bsc_page_3.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/pages/ant_bsc_page_4.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/pages/ant_bsc_page_5.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/simulator/ant_bsc_simulator.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/ant_bsc.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_common/ant_request_controller/ant_request_controller.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_common/pages/ant_common_page_70.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_common/pages/ant_common_page_80.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_common/pages/ant_common_page_81.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/pages/ant_hrm_page_0.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/pages/ant_hrm_page_1.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/pages/ant_hrm_page_2.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/pages/ant_hrm_page_3.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/pages/ant_hrm_page_4.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/simulator/ant_hrm_simulator.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/ant_hrm.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/pages/ant_sdm_common_data.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/pages/ant_sdm_page_1.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/pages/ant_sdm_page_16.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/pages/ant_sdm_page_2.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/pages/ant_sdm_page_22.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/pages/ant_sdm_page_3.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/simulator/ant_sdm_simulator.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/ant_sdm.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_search_config/ant_search_config.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_stack_config/ant_stack_config.c
#SRC_FILES += $(SDK_ROOT)/components/ant/ant_state_indicator/ant_state_indicator.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_advertising/ble_advertising.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_db_discovery/ble_db_discovery.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_debug_assert_handler/ble_debug_assert_handler.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_dtm/ble_dtm.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_dtm/ble_dtm_hw_nrf51.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_dtm/ble_dtm_hw_nrf52.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_error_log/ble_error_log.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_racp/ble_racp.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_radio_notification/ble_radio_notification.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_ancs_c/ancs_app_attr_get.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_ancs_c/ancs_attr_parser.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_ancs_c/ancs_tx_buffer.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_ancs_c/nrf_ble_ancs_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_ans_c/ble_ans_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_bas/ble_bas.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_bas_c/ble_bas_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_bps/ble_bps.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_cscs/ble_cscs.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_cscs/ble_sc_ctrlpt.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_cts_c/ble_cts_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_dfu/ble_dfu.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_dis/ble_dis.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_escs/nrf_ble_escs.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_gls/ble_gls.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_gls/ble_gls_db.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_hids/ble_hids.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_hrs/ble_hrs.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_hrs_c/ble_hrs_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_hts/ble_hts.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_ias/ble_ias.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_ias_c/ble_ias_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_lbs/ble_lbs.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_lbs_c/ble_lbs_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_lls/ble_lls.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_nus/ble_nus.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_nus_c/ble_nus_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_rscs/ble_rscs.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_rscs_c/ble_rscs_c.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/ble_tps/ble_tps.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_ble_lns/ble_lns.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_ble_lns/ble_ln_cp.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_ble_lns/ble_ln_db.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_bms/nrf_ble_bms.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_cgms/cgms_db.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_cgms/cgms_meas.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_cgms/cgms_racp.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_cgms/cgms_socp.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_cgms/cgms_sst.c
#SRC_FILES += $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_cgms/nrf_ble_cgms.c
SRC_FILES += $(SDK_ROOT)/components/ble/common/ble_advdata.c
#SRC_FILES += $(SDK_ROOT)/components/ble/common/ble_conn_params.c
#SRC_FILES += $(SDK_ROOT)/components/ble/common/ble_conn_state.c
#SRC_FILES += $(SDK_ROOT)/components/ble/common/ble_srv_common.c
#SRC_FILES += $(SDK_ROOT)/components/ble/nrf_ble_gatt/nrf_ble_gatt.c
#SRC_FILES += $(SDK_ROOT)/components/ble/nrf_ble_qwr/nrf_ble_qwr.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/gatts_cache_manager.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/gatt_cache_manager.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/id_manager.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/peer_data.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/peer_database.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/peer_data_storage.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/peer_id.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/peer_manager.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/pm_buffer.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/pm_mutex.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/security_dispatcher.c
#SRC_FILES += $(SDK_ROOT)/components/ble/peer_manager/security_manager.c
SRC_FILES += $(SDK_ROOT)/components/boards/boards.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/adns2080/adns2080.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/cherry8x16/cherry8x16.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/ds1624/ds1624.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/max9850/max9850.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/mcp4725/mcp4725.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/mpu6050/mpu6050.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/nrf6350/nrf6350.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/synaptics_touchpad/synaptics_touchpad.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_ext/uda1380/uda1380.c
SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/adc/nrf_drv_adc.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/ble_flash/ble_flash.c
SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/clock/nrf_drv_clock.c
SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/common/nrf_drv_common.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/comp/nrf_drv_comp.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/gpiote/nrf_drv_gpiote.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/hal/nrf_adc.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/hal/nrf_ecb.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/hal/nrf_nvmc.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/hal/nrf_saadc.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/i2s/nrf_drv_i2s.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/lpcomp/nrf_drv_lpcomp.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd/nrf_nvic.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/pdm/nrf_drv_pdm.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/power/nrf_drv_power.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/ppi/nrf_drv_ppi.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/pwm/nrf_drv_pwm.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/qdec/nrf_drv_qdec.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/qspi/nrf_drv_qspi.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/radio_config/radio_config.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/rng/nrf_drv_rng.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/rtc/nrf_drv_rtc.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/saadc/nrf_drv_saadc.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/sdio/sdio.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/spi_master/nrf_drv_spi.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/spi_master/spi_5W_master.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/spi_slave/nrf_drv_spis.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/swi/nrf_drv_swi.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/systick/nrf_drv_systick.c
SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/timer/nrf_drv_timer.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/twis_slave/nrf_drv_twis.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/twi_master/deprecated/twi_hw_master.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/twi_master/deprecated/twi_sw_master.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/twi_master/nrf_drv_twi.c
SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/uart/nrf_drv_uart.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/usbd/nrf_drv_usbd.c
#SRC_FILES += $(SDK_ROOT)/components/drivers_nrf/wdt/nrf_drv_wdt.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/atomic_fifo/app_atfifo.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/balloc/nrf_balloc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/block_dev/empty/nrf_block_dev_empty.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/block_dev/qspi/nrf_block_dev_qspi.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/block_dev/qspi/nrf_serial_flash_params.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/block_dev/ram/nrf_block_dev_ram.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/block_dev/sdc/nrf_block_dev_sdc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/ble_dfu/nrf_ble_dfu.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/dfu/nrf_dfu.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/dfu/nrf_dfu_flash.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/dfu/nrf_dfu_mbr.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/dfu/nrf_dfu_settings.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/dfu/nrf_dfu_transport.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/dfu/nrf_dfu_utils.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/nrf_bootloader.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/nrf_bootloader_app_start.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bootloader/nrf_bootloader_info.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bsp/bsp.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bsp/bsp_btn_ant.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bsp/bsp_btn_ble.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/bsp/bsp_nfc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/button/app_button.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/crc16/crc16.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/crc32/crc32.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/crypto/nrf_crypto.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/crypto/nrf_crypto_svc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/csense/nrf_csense.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/csense_drv/nrf_drv_csense.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/ecc/ecc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_adv.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_adv_frame.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_adv_timing.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_adv_timing_resolver.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_battery_voltage_adc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_battery_voltage_saadc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_flash.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_gatts.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_gatts_read.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_gatts_write.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_security.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_security_timing.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_slot.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_slot_reg.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_stopwatch.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/es_tlm.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/eddystone/nrf_ble_es.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/fds/fds.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/fifo/app_fifo.c
SRC_FILES += $(SDK_ROOT)/components/libraries/fstorage/fstorage.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/fstorage/fstorage_nosd.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/gpiote/app_gpiote.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hardfault/nrf51/handler/hardfault_handler_gcc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hardfault/nrf51/handler/hardfault_handler_iar.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hardfault/nrf51/handler/hardfault_handler_keil.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hardfault/nrf52/handler/hardfault_handler_gcc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hardfault/nrf52/handler/hardfault_handler_iar.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hardfault/nrf52/handler/hardfault_handler_keil.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hardfault/hardfault_implementation.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hci/hci_mem_pool.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hci/hci_slip.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/hci/hci_transport.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/ic_info/nrf_ic_info.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/led_softblink/led_softblink.c
SRC_FILES += $(SDK_ROOT)/components/libraries/log/src/nrf_log_backend_serial.c
SRC_FILES += $(SDK_ROOT)/components/libraries/log/src/nrf_log_frontend.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/low_power_pwm/low_power_pwm.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/mailbox/app_mailbox.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/mem_manager/mem_manager.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/pwm/app_pwm.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/queue/nrf_queue.c
SRC_FILES += $(SDK_ROOT)/components/libraries/scheduler/app_scheduler.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/scheduler/app_scheduler_serconn.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/sdcard/app_sdcard.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/sensorsim/sensorsim.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/sha256/sha256.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/simple_timer/app_simple_timer.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/slip/slip.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/svc/nrf_svc_handler.c
SRC_FILES += $(SDK_ROOT)/components/libraries/timer/app_timer.c
SRC_FILES += $(SDK_ROOT)/components/libraries/timer/app_timer_appsh.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/timer/app_timer_ble_gzll.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/timer/app_timer_freertos.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/timer/app_timer_rtx.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/twi/app_twi.c
SRC_FILES += $(SDK_ROOT)/components/libraries/uart/app_uart.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/uart/app_uart_fifo.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/uart/retarget.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/class/audio/app_usbd_audio.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/class/cdc/acm/app_usbd_cdc_acm.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/class/hid/generic/app_usbd_hid_generic.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/class/hid/kbd/app_usbd_hid_kbd.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/class/hid/mouse/app_usbd_hid_mouse.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/class/hid/app_usbd_hid.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/class/msc/app_usbd_msc.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/app_usbd.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/app_usbd_core.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/usbd/app_usbd_string_desc.c
SRC_FILES += $(SDK_ROOT)/components/libraries/util/app_error.c
SRC_FILES += $(SDK_ROOT)/components/libraries/util/app_error_weak.c
SRC_FILES += $(SDK_ROOT)/components/libraries/util/app_util_platform.c
SRC_FILES += $(SDK_ROOT)/components/libraries/util/nrf_assert.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/util/sdk_errors.c
#SRC_FILES += $(SDK_ROOT)/components/libraries/util/sdk_mapped_flags.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/experimental_t4t_lib/hal_t4t/hal_nfc_t4t.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/connection_handover/ac_rec/nfc_ac_rec.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/connection_handover/ble_oob_advdata/nfc_ble_oob_advdata.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/connection_handover/ble_pair_msg/nfc_ble_pair_msg.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/connection_handover/common/nfc_ble_pair_common.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/connection_handover/ep_oob_rec/nfc_ep_oob_rec.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/connection_handover/hs_rec/nfc_hs_rec.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/connection_handover/le_oob_rec/nfc_le_oob_rec.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/generic/message/nfc_ndef_msg.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/generic/record/nfc_ndef_record.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/launchapp/nfc_launchapp_msg.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/launchapp/nfc_launchapp_rec.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/parser/message/nfc_ndef_msg_parser.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/parser/message/nfc_ndef_msg_parser_local.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/parser/record/nfc_ndef_record_parser.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/text/nfc_text_rec.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/uri/nfc_uri_msg.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/ndef/uri/nfc_uri_rec.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/t2t_lib/hal_t2t/hal_nfc_t2t.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/t2t_parser/nfc_t2t_parser.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/t4t_parser/apdu/nfc_t4t_apdu.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/t4t_parser/cc_file/nfc_t4t_cc_file.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/t4t_parser/hl_detection_procedure/nfc_t4t_hl_detection_procedures.c
#SRC_FILES += $(SDK_ROOT)/components/nfc/t4t_parser/tlv/nfc_t4t_tlv_block.c
#SRC_FILES += $(SDK_ROOT)/components/proprietary_rf/esb/nrf_esb.c
#SRC_FILES += $(SDK_ROOT)/components/proprietary_rf/gzll/nrf_gzp.c
#SRC_FILES += $(SDK_ROOT)/components/proprietary_rf/gzll/nrf_gzp_device.c
#SRC_FILES += $(SDK_ROOT)/components/proprietary_rf/gzll/nrf_gzp_host.c
#SRC_FILES += $(SDK_ROOT)/components/proprietary_rf/gzll/nrf_gzp_host_nrf5x.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/common/ble_dtm_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/common/ble_dtm_init.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/common/conn_systemreset.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/middleware/app_mw_ble.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/middleware/app_mw_ble_gap.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/middleware/app_mw_ble_gattc.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/middleware/app_mw_ble_gatts.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/middleware/app_mw_ble_l2cap.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/middleware/app_mw_nrf_soc.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/app_ble_gap_sec_keys.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/app_ble_user_mem.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_event.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_evt_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_gap_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_gap_evt_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_gattc_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_gattc_evt_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_gatts_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_gatts_evt_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_l2cap_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/ble_l2cap_evt_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/codecs/s132/serializers/nrf_soc_app.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/hal/ser_app_hal_nrf5x.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/hal/ser_app_power_system_off.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/application/transport/ser_sd_transport.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/struct_ser/s132/ble_gap_struct_serialization.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/struct_ser/s132/ble_gattc_struct_serialization.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/struct_ser/s132/ble_gatts_struct_serialization.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/struct_ser/s132/ble_gatt_struct_serialization.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/struct_ser/s132/ble_struct_serialization.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/struct_ser/s132/nrf_soc_struct_serialization.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy_hci.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy_hci_slip.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy_nohci.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy_spi_5W_master.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy_spi_5W_slave.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy_spi_master.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy_spi_slave.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_phy/ser_phy_uart.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/transport/ser_hal_transport.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/ble_serialization.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/cond_field_serialization.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/common/ser_dbg_sd_str.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/common/ble_dtm_init.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/common/conn_mw.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/middleware/conn_mw_ble.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/middleware/conn_mw_ble_gap.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/middleware/conn_mw_ble_gattc.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/middleware/conn_mw_ble_gatts.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/middleware/conn_mw_ble_l2cap.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/middleware/conn_mw_items.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/middleware/conn_mw_nrf_soc.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_event_enc.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_evt_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_gap_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_gap_evt_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_gattc_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_gattc_evt_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_gatts_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_gatts_evt_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_l2cap_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/ble_l2cap_evt_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/conn_ble_gap_sec_keys.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/conn_ble_user_mem.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/codecs/s132/serializers/nrf_soc_conn.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/hal/dtm_uart.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/ser_conn_cmd_decoder.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/ser_conn_dtm_cmd_decoder.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/ser_conn_error_handling.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/ser_conn_event_encoder.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/ser_conn_handlers.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/ser_conn_pkt_decoder.c
#SRC_FILES += $(SDK_ROOT)/components/serialization/connectivity/ser_conn_reset_cmd_decoder.c
SRC_FILES += $(SDK_ROOT)/components/toolchain/system_nrf51.c
#SRC_FILES += $(SDK_ROOT)/components/toolchain/system_nrf51422.c
#SRC_FILES += $(SDK_ROOT)/components/toolchain/system_nrf52.c
#SRC_FILES += $(SDK_ROOT)/components/toolchain/system_nrf52840.c
#SRC_FILES += $(SDK_ROOT)/external/cifra_AES128-EAX/blockwise.c
#SRC_FILES += $(SDK_ROOT)/external/cifra_AES128-EAX/cifra_eax_aes.c
#SRC_FILES += $(SDK_ROOT)/external/cifra_AES128-EAX/cmac.c
#SRC_FILES += $(SDK_ROOT)/external/cifra_AES128-EAX/eax.c
#SRC_FILES += $(SDK_ROOT)/external/cifra_AES128-EAX/gf128.c
#SRC_FILES += $(SDK_ROOT)/external/cifra_AES128-EAX/modes.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/doc/res/app1.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/doc/res/app2.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/doc/res/app3.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/doc/res/app4.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/port/diskio_blkdev.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/option/cc932.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/option/cc936.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/option/cc949.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/option/cc950.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/option/ccsbcs.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/option/syscall.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/option/unicode.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/diskio.c
#SRC_FILES += $(SDK_ROOT)/external/fatfs/src/ff.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/ARM/nrf51/port.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/ARM/nrf52/port.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/CMSIS/nrf51/port_cmsis.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/CMSIS/nrf51/port_cmsis_systick.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/CMSIS/nrf52/port_cmsis.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/CMSIS/nrf52/port_cmsis_systick.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/GCC/nrf51/port.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/GCC/nrf52/port.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/IAR/nrf51/port.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/portable/IAR/nrf52/port.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/portable/MemMang/heap_1.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/portable/MemMang/heap_2.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/portable/MemMang/heap_3.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/portable/MemMang/heap_4.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/portable/MemMang/heap_5.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/croutine.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/event_groups.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/list.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/queue.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/tasks.c
#SRC_FILES += $(SDK_ROOT)/external/freertos/source/timers.c
#SRC_FILES += $(SDK_ROOT)/external/nano-pb/pb_common.c
#SRC_FILES += $(SDK_ROOT)/external/nano-pb/pb_decode.c
#SRC_FILES += $(SDK_ROOT)/external/nano-pb/pb_encode.c
#SRC_FILES += $(SDK_ROOT)/external/nfc_adafruit_library/adafruit_pn532.c
#SRC_FILES += $(SDK_ROOT)/external/nrf_cc310/common/integration_test_plat_utils.c
#SRC_FILES += $(SDK_ROOT)/external/protothreads/pt-1.4/example-buffer.c
#SRC_FILES += $(SDK_ROOT)/external/protothreads/pt-1.4/example-codelock.c
#SRC_FILES += $(SDK_ROOT)/external/protothreads/pt-1.4/example-small.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/port/RTX_Conf_CM.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/HAL_CM.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_CMSIS.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Event.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_List.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Mailbox.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_MemBox.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Memory.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Mutex.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Robin.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Semaphore.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_System.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Task.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Time.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/source/rt_Timer.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_GenWait.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_MailQueue.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_MemoryPool.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_MsgQueue.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_Mutex.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_Semaphore.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_Signal.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_Thread.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_Timer.c
#SRC_FILES += $(SDK_ROOT)/external/rtx/validation/source/RV_WaitFunc.c
#SRC_FILES += $(SDK_ROOT)/external/segger_rtt/RTT_Syscalls_GCC.c
#SRC_FILES += $(SDK_ROOT)/external/segger_rtt/RTT_Syscalls_IAR.c
#SRC_FILES += $(SDK_ROOT)/external/segger_rtt/RTT_Syscalls_KEIL.c
#SRC_FILES += $(SDK_ROOT)/external/segger_rtt/SEGGER_RTT.c
#SRC_FILES += $(SDK_ROOT)/external/segger_rtt/SEGGER_RTT_printf.c

ifeq ($(PARAM_SOFTDEVICE), S130)
	#SRC_FILES += $(SDK_ROOT)/components/serialization/application/transport/ser_softdevice_handler.c
	SRC_FILES += $(SDK_ROOT)/components/softdevice/common/softdevice_handler/softdevice_handler.c
	#SRC_FILES += $(SDK_ROOT)/components/softdevice/common/softdevice_handler/softdevice_handler_appsh.c
endif


# Include folders common to all targets
INC_FOLDERS += $(PROJ_DIR)
INC_FOLDERS+= $(SDK_ROOT)/components/boards
INC_FOLDERS+= $(SDK_ROOT)/components/device
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/adns2080
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/cherry8x16
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/ds1624
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/max9850
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/mcp4725
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/mpu6050
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/nrf6350
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/synaptics_touchpad
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_ext/uda1380
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/adc
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/ble_flash
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/clock
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/common
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/comp
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/delay
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/gpiote
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/hal
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/i2s
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/lpcomp
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/pdm
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/power
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/ppi
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/pwm
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/qdec
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/qspi
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/radio_config
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/rng
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/rtc
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/saadc
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/sdio/config
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/sdio
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/spi_master
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/spi_slave
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/swi
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/systick
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/timer
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/twis_slave
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/twi_master/deprecated/config
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/twi_master/deprecated
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/twi_master
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/uart
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/usbd
INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/wdt
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/atomic
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/atomic_fifo
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/balloc
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/block_dev/empty
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/block_dev/qspi
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/block_dev/ram
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/block_dev/sdc
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/block_dev
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/bootloader/ble_dfu
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/bootloader/dfu
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/bootloader
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/bsp
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/button
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/crc16
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/crc32
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/crypto
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/csense
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/csense_drv
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/ecc
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/eddystone
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/experimental_section_vars
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/fds
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/fifo
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/fstorage
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/gpiote
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/hardfault
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/hci
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/ic_info
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/led_softblink
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/log/src
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/log
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/low_power_pwm
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/mailbox
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/mem_manager
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/pwm
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/pwr_mgmt
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/queue
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/scheduler
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/sdcard
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/sensorsim
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/sha256
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/simple_timer
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/slip
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/svc
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/timer
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/twi
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/uart
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/class/audio
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/class/cdc/acm
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/class/cdc
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/class/hid/generic
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/class/hid/kbd
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/class/hid/mouse
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/class/hid
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/class/msc
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd/config
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/usbd
INC_FOLDERS+= $(SDK_ROOT)/components/libraries/util
INC_FOLDERS+= $(SDK_ROOT)/components/proprietary_rf/esb
INC_FOLDERS+= $(SDK_ROOT)/components/proprietary_rf/gzll/config
INC_FOLDERS+= $(SDK_ROOT)/components/proprietary_rf/gzll
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/application/codecs/common
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/application/hal
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/application/transport
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/common/struct_ser/s132
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/common/transport/ser_phy/config
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/common/transport/ser_phy
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/common/transport
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/common
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/connectivity/codecs/common
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/connectivity/hal
INC_FOLDERS+= $(SDK_ROOT)/components/serialization/connectivity
INC_FOLDERS+= $(SDK_ROOT)/components/toolchain/arm
INC_FOLDERS+= $(SDK_ROOT)/components/toolchain/cmsis/include
INC_FOLDERS+= $(SDK_ROOT)/components/toolchain
INC_FOLDERS+= $(SDK_ROOT)/components
INC_FOLDERS+= $(SDK_ROOT)/external/cifra_AES128-EAX
INC_FOLDERS+= $(SDK_ROOT)/external/fatfs/port
INC_FOLDERS+= $(SDK_ROOT)/external/fatfs/src
INC_FOLDERS+= $(SDK_ROOT)/external/freertos/config
INC_FOLDERS+= $(SDK_ROOT)/external/freertos/portable/ARM/nrf51
#INC_FOLDERS+= $(SDK_ROOT)/external/freertos/portable/ARM/nrf52
INC_FOLDERS+= $(SDK_ROOT)/external/freertos/portable/CMSIS/nrf51
#INC_FOLDERS+= $(SDK_ROOT)/external/freertos/portable/CMSIS/nrf52
INC_FOLDERS+= $(SDK_ROOT)/external/freertos/portable/GCC/nrf51
#INC_FOLDERS+= $(SDK_ROOT)/external/freertos/portable/GCC/nrf52
INC_FOLDERS+= $(SDK_ROOT)/external/freertos/portable/IAR/nrf51
#INC_FOLDERS+= $(SDK_ROOT)/external/freertos/portable/IAR/nrf52
INC_FOLDERS+= $(SDK_ROOT)/external/freertos/source/include
INC_FOLDERS+= $(SDK_ROOT)/external/nano-pb
INC_FOLDERS+= $(SDK_ROOT)/external/nfc_adafruit_library
INC_FOLDERS+= $(SDK_ROOT)/external/nrf_cc310/common
INC_FOLDERS+= $(SDK_ROOT)/external/nrf_cc310/include
INC_FOLDERS+= $(SDK_ROOT)/external/protothreads/pt-1.4
INC_FOLDERS+= $(SDK_ROOT)/external/protothreads
INC_FOLDERS+= $(SDK_ROOT)/external/rtx/include
INC_FOLDERS+= $(SDK_ROOT)/external/rtx/source
INC_FOLDERS+= $(SDK_ROOT)/external/rtx/validation/include
INC_FOLDERS+= $(SDK_ROOT)/external/segger_rtt
INC_FOLDERS+= $(SDK_ROOT)/external/tiny-AES128

ifeq ($(PARAM_SOFTDEVICE), S130)
	INC_FOLDERS += $(SDK_ROOT)/components/softdevice/s130/headers/nrf51
	INC_FOLDERS += $(SDK_ROOT)/components/softdevice/s130/headers
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_channel_config
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_encryption
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_fs
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_key_manager/config
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_key_manager
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/pages
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/simulator
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr/utils
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_bpwr
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/pages
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/simulator
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc/utils
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_bsc
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_common/ant_request_controller
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_common/pages
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/pages
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/simulator
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm/utils
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_hrm
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/pages
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/simulator
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm/utils
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_profiles/ant_sdm
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_search_config
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_stack_config/config
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_stack_config
	INC_FOLDERS+= $(SDK_ROOT)/components/ant/ant_state_indicator
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_advertising
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_db_discovery
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_debug_assert_handler
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_dtm
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_error_log
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_racp
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_radio_notification
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_ancs_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_ans_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_bas
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_bas_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_bps
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_cscs
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_cts_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_dfu
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_dis
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_escs
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_gls
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_hids
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_hrs
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_hrs_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_hts
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_ias
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_ias_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_lbs
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_lbs_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_lls
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_nus
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_nus_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_rscs
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_rscs_c
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/ble_tps
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/experimental_ble_lns
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_bms
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/ble_services/experimental_nrf_ble_cgms
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/common
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/nrf_ble_gatt
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/nrf_ble_qwr
	INC_FOLDERS+= $(SDK_ROOT)/components/ble/peer_manager
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/experimental_t4t_lib/hal_t4t
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/experimental_t4t_lib
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/connection_handover/ac_rec
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/connection_handover/ble_oob_advdata
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/connection_handover/ble_pair_msg
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/connection_handover/common
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/connection_handover/ep_oob_rec
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/connection_handover/hs_rec
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/connection_handover/le_oob_rec
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/generic/message
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/generic/record
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/launchapp
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/parser/message
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/parser/record
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/text
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/ndef/uri
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/t2t_lib/hal_t2t
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/t2t_lib
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/t2t_parser
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/t4t_parser/apdu
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/t4t_parser/cc_file
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/t4t_parser/hl_detection_procedure
	INC_FOLDERS+= $(SDK_ROOT)/components/nfc/t4t_parser/tlv
	INC_FOLDERS+= $(SDK_ROOT)/components/softdevice/common/softdevice_handler
	INC_FOLDERS+= $(SDK_ROOT)/components/softdevice/s130/headers/nrf51
	INC_FOLDERS+= $(SDK_ROOT)/components/softdevice/s130/headers
	#INC_FOLDERS+= $(SDK_ROOT)/components/softdevice/s132/headers/nrf52
	#INC_FOLDERS+= $(SDK_ROOT)/components/softdevice/s132/headers
	#INC_FOLDERS+= $(SDK_ROOT)/components/softdevice/s212/headers
	#INC_FOLDERS+= $(SDK_ROOT)/components/softdevice/s332/headers
else
	INC_FOLDERS+= $(SDK_ROOT)/components/drivers_nrf/nrf_soc_nosd	
endif

# Libraries common to all targets
LIB_FILES += \

# C flags common to all targets
CFLAGS += -DBOARD_CUSTOM
CFLAGS += -DNRF51
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DSWI_DISABLE0
CFLAGS += -DBSP_DEFINES_ONLY
CFLAGS += -DNRF51822
CFLAGS += -DDEBUG_NRF_USER
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs
CFLAGS +=  -Wall -Werror
ifeq ($(PARAM_VARIANT), DEBUG)
	CFLAGS += -g
else ifeq ($(PARAM_VARIANT), RELEASE_PROD)
	CFLAGS += -DNRF_LOG_DEFAULT_LEVEL=0
	CFLAGS += -O3
else
	CFLAGS += -O3
endif
CFLAGS += -mfloat-abi=soft
# keep every function in separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums 

ifeq ($(PARAM_SOFTDEVICE), S130)
	CFLAGS += -DSOFTDEVICE_PRESENT
	CFLAGS += -DS130
	CFLAGS += -DNRF_SD_BLE_API_VERSION=2
endif

# C++ flags common to all targets
CXXFLAGS += -std=c++11
CXXFLAGS += -fno-threadsafe-statics -fno-exceptions -fno-rtti
ifeq ($(PARAM_VARIANT), DEBUG)
	CXXFLAGS += -g
else ifeq ($(PARAM_VARIANT), RELEASE_PROD)
	CFLAGS += -DNRF_LOG_DEFAULT_LEVEL=0
else
	CXXFLAGS += -O3
endif
CXXFLAGS += -DDEBUG_NRF_USER

ifeq ($(PARAM_SOFTDEVICE), S130)
	CXXFLAGS += -DSOFTDEVICE_PRESENT
	CXXFLAGS += -DS130
	CXXFLAGS += -DNRF_SD_BLE_API_VERSION=2
endif

# Assembler flags common to all targets
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DBOARD_PCA10028
ASMFLAGS += -DNRF51
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DSWI_DISABLE0
ASMFLAGS += -DBSP_DEFINES_ONLY
ASMFLAGS += -DNRF51422
ASMFLAGS += -D__HEAP_SIZE=1024 -D__STACK_SIZE=1024

ifeq ($(PARAM_SOFTDEVICE), S130)
	ASMFLAGS += -DSOFTDEVICE_PRESENT
	ASMFLAGS += -DS130
	ASMFLAGS += -DNRF_SD_BLE_API_VERSION=2
endif

# Linker flags
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -T$(LINKER_SCRIPT)
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys

.PHONY: $(TARGETS) default all clean help flash

# Default target - first one defined
default: $(OUTPUT_DIRECTORY)/nrf51822_xxaa.hex

# Print all targets that can be built
help:
	@echo following targets are available:
	@echo 	nrf51822_xxaa

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc

include $(TEMPLATE_PATH)/Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

clean_all:
	$(RM) output



flash_softdevice:
	$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gdb --command erase.gdb
	$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gdb --command flash.gdb $(SDK_ROOT)/components/softdevice/s130/hex/s130_nrf51_2.0.1_softdevice.hex

flash: $(OUTPUT_DIRECTORY)/nrf51822_xxaa.hex
	$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gdb --command flash.gdb $(OUTPUT_DIRECTORY)/nrf51822_xxaa.hex
