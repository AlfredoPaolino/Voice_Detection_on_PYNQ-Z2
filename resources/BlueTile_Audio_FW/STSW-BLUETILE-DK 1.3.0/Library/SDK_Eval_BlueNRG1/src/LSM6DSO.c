/*
 ******************************************************************************
 * @file    lsm6dso_reg.c
 * @author  Sensor Solutions Software Team
 * @brief   LSM6DSO driver file
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "LSM6DSO.h"
#include "LSM6DSO_hal.h"

/**
 * @addtogroup  lsm6dso
 * @brief  This file provides a set of functions needed to drive the
 *         lsm6dso enanced inertial module.
 * @{
 */

/**
 * @addtogroup  interfaces_functions
 * @brief  This section provide a set of functions used to read and write
 *         a generic register of the device.
 * @{
 */

/**
 * @brief  Read generic device register
 *
 * @param  lsm6dso_ctx_t* ctx: read / write interface definitions
 * @param  uint8_t reg: register to read
 * @param  uint8_t* data: pointer to buffer that store the data read
 * @param  uint16_t len: number of consecutive register to read
 *
 */
int32_t lsm6dso_read_reg(lsm6dso_ctx_t* ctx, uint8_t reg, uint8_t* data, uint16_t len) {
	return LSM6DSO_IO_Read(data, LSM6DSO_I2C_ADD_H, reg, len);
}

/**
 * @brief  Write generic device register
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t reg: register to write
 * @param  uint8_t* data: pointer to data to write in register reg
 * @param  uint16_t len: number of consecutive register to write
 *
 */
int32_t lsm6dso_write_reg(lsm6dso_ctx_t* ctx, uint8_t reg, uint8_t* data, uint16_t len) {
	return LSM6DSO_IO_Write(data, LSM6DSO_I2C_ADD_H, reg, len);
}

/**
 * @}
 */

/**
 * @addtogroup  data_generation_c
 * @brief   This section groups all the functions concerning data generation
 * @{
 */

/**
 * @brief  xl_full_scale: [set]  Accelerometer full-scale selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fs_xl_t: change the values of fs_xl in reg CTRL1_XL
 *
 */
int32_t lsm6dso_xl_full_scale_set(lsm6dso_ctx_t *ctx, lsm6dso_fs_xl_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);
	reg.ctrl1_xl.fs_xl = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_full_scale: [get]  Accelerometer full-scale selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fs_xl_t: Get the values of fs_xl in reg CTRL1_XL
 *
 */
int32_t lsm6dso_xl_full_scale_get(lsm6dso_ctx_t *ctx, lsm6dso_fs_xl_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);
	*val = (lsm6dso_fs_xl_t) reg.ctrl1_xl.fs_xl;

	return mm_error;
}

/**
 * @brief  xl_data_rate: [set]  Accelerometer UI data rate selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_odr_xl_t: change the values of odr_xl in reg CTRL1_XL
 *
 */
int32_t lsm6dso_xl_data_rate_set(lsm6dso_ctx_t *ctx, lsm6dso_odr_xl_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);
	reg.ctrl1_xl.odr_xl = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_data_rate: [get]  Accelerometer UI data rate selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_odr_xl_t: Get the values of odr_xl in reg CTRL1_XL
 *
 */
int32_t lsm6dso_xl_data_rate_get(lsm6dso_ctx_t *ctx, lsm6dso_odr_xl_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);
	*val = (lsm6dso_odr_xl_t) reg.ctrl1_xl.odr_xl;

	return mm_error;
}

/**
 * @brief  gy_full_scale: [set]  Gyroscope UI chain full-scale selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fs_g_t: change the values of fs_g in reg CTRL2_G
 *
 */
int32_t lsm6dso_gy_full_scale_set(lsm6dso_ctx_t *ctx, lsm6dso_fs_g_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL2_G, &reg.byte, 1);
	reg.ctrl2_g.fs_g = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL2_G, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  gy_full_scale: [get]  Gyroscope UI chain full-scale selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fs_g_t: Get the values of fs_g in reg CTRL2_G
 *
 */
int32_t lsm6dso_gy_full_scale_get(lsm6dso_ctx_t *ctx, lsm6dso_fs_g_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL2_G, &reg.byte, 1);
	*val = (lsm6dso_fs_g_t) reg.ctrl2_g.fs_g;

	return mm_error;
}

/**
 * @brief  gy_data_rate: [set]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_odr_g_t: change the values of odr_g in reg CTRL2_G
 *
 */
int32_t lsm6dso_gy_data_rate_set(lsm6dso_ctx_t *ctx, lsm6dso_odr_g_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL2_G, &reg.byte, 1);
	reg.ctrl2_g.odr_g = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL2_G, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  gy_data_rate: [get]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_odr_g_t: Get the values of odr_g in reg CTRL2_G
 *
 */
int32_t lsm6dso_gy_data_rate_get(lsm6dso_ctx_t *ctx, lsm6dso_odr_g_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL2_G, &reg.byte, 1);
	*val = (lsm6dso_odr_g_t) reg.ctrl2_g.odr_g;

	return mm_error;
}

/**
 * @brief  block_data_update: [set] Blockdataupdate.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of bdu in reg CTRL3_C
 *
 */
int32_t lsm6dso_block_data_update_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	reg.ctrl3_c.bdu = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  block_data_update: [get] Blockdataupdate.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of bdu in reg CTRL3_C
 *
 */
int32_t lsm6dso_block_data_update_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	*val = reg.ctrl3_c.bdu;

	return mm_error;
}

/**
 * @brief  xl_offset_weight: [set] Weight of XL user offset bits of
 *                                 registers X_OFS_USR (73h), Y_OFS_USR (74h),
 *                                 Z_OFS_USR (75h)
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_usr_off_w_t: change the values of usr_off_w in reg CTRL6_C
 *
 */
int32_t lsm6dso_xl_offset_weight_set(lsm6dso_ctx_t *ctx, lsm6dso_usr_off_w_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);
	reg.ctrl6_c.usr_off_w = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_offset_weight: [get] Weight of XL user offset bits of
 *                                 registers X_OFS_USR (73h),
 *                                 Y_OFS_USR (74h), Z_OFS_USR (75h)
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_usr_off_w_t: Get the values of usr_off_w in reg CTRL6_C
 *
 */
int32_t lsm6dso_xl_offset_weight_get(lsm6dso_ctx_t *ctx, lsm6dso_usr_off_w_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);
	*val = (lsm6dso_usr_off_w_t) reg.ctrl6_c.usr_off_w;

	return mm_error;
}

/**
 * @brief  xl_power_mode: [set]  Accelerometer power mode
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_xl_hm_mode_t: change the values of xl_hm_mode in
 *                               reg CTRL6_C
 *
 */
int32_t lsm6dso_xl_power_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_xl_hm_mode_t val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL5_C, &reg[0].byte, 2);
	reg[0].ctrl5_c.xl_ulp_en = (val & 0x02) >> 1;
	reg[1].ctrl6_c.xl_hm_mode = val & 0x01;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL5_C, &reg[0].byte, 2);

	return mm_error;
}

/**
 * @brief  xl_power_mode: [get]  Accelerometer power mode
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_xl_hm_mode_t: Get the values of xl_hm_mode in reg CTRL6_C
 *
 */
int32_t lsm6dso_xl_power_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_xl_hm_mode_t *val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL5_C, &reg[0].byte, 2);
	*val = (lsm6dso_xl_hm_mode_t) (reg[0].ctrl5_c.xl_ulp_en << 1);
	*val |= (lsm6dso_xl_hm_mode_t) reg[1].ctrl6_c.xl_hm_mode;

	return mm_error;
}

/**
 * @brief  gy_power_mode: [set]  Operating mode for gyroscope.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_g_hm_mode_t: change the values of g_hm_mode in reg CTRL7_G
 *
 */
int32_t lsm6dso_gy_power_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_g_hm_mode_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);
	reg.ctrl7_g.g_hm_mode = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  gy_power_mode: [get]  Operating mode for gyroscope.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_g_hm_mode_t: Get the values of g_hm_mode in reg CTRL7_G
 *
 */
int32_t lsm6dso_gy_power_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_g_hm_mode_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);
	*val = (lsm6dso_g_hm_mode_t) reg.ctrl7_g.g_hm_mode;

	return mm_error;
}

/**
 * @brief  all_sources: [get]  Read all the interrupt flag of the device.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_all_sources: registers ALL_INT_SRC; WAKE_UP_SRC;
 *                              TAP_SRC; D6D_SRC; STATUS_REG;
 *                              EMB_FUNC_STATUS; FSM_STATUS_A/B
 *
 */
int32_t lsm6dso_all_sources_get(lsm6dso_ctx_t *ctx, lsm6dso_all_sources_t *val) {
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_ALL_INT_SRC, val->byte, 5);

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_STATUS, &val->byte[5], 3);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @brief  status_reg: [get] The STATUS_REG register is read by the
 *                           primary interface
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_status_reg_t: register STATUS_REG
 *
 */
int32_t lsm6dso_status_reg_get(lsm6dso_ctx_t *ctx, lsm6dso_status_reg_t *val) {
	return lsm6dso_read_reg(ctx, LSM6DSO_STATUS_REG, (uint8_t*) val, 1);
}
/**
 * @brief  xl_flag_data_ready: [get]  Accelerometer new data available.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of xlda in reg STATUS_REG
 *
 */
int32_t lsm6dso_xl_flag_data_ready_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_STATUS_REG, &reg.byte, 1);
	*val = reg.status_reg.xlda;

	return mm_error;
}
/**
 * @brief  gy_flag_data_ready: [get]  Gyroscope new data available.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of gda in reg STATUS_REG
 *
 */
int32_t lsm6dso_gy_flag_data_ready_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_STATUS_REG, &reg.byte, 1);
	*val = reg.status_reg.gda;

	return mm_error;
}
/**
 * @brief   temp_flag_data_ready: [get]  Temperature new data available.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tda in reg STATUS_REG
 *
 */
int32_t lsm6dso_temp_flag_data_ready_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_STATUS_REG, &reg.byte, 1);
	*val = reg.status_reg.tda;

	return mm_error;
}
/**
 * @brief  xl_usr_offset_x: [set] Accelerometer X-axis user offset
 *                                correction expressed in two’s complement,
 *                                weight depends on USR_OFF_W in
 *                                CTRL6_C (15h).
 *                                The value must be in the range [-127 127].
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_xl_usr_offset_x_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_write_reg(ctx, LSM6DSO_X_OFS_USR, buff, 1);
}

/**
 * @brief  xl_usr_offset_x: [get] Accelerometer X-axis user offset
 *                                correction expressed in two’s complement,
 *                                weight depends on USR_OFF_W in
 *                                CTRL6_C (15h). The value must be in the
 *                                range [-127 127].
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_xl_usr_offset_x_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_X_OFS_USR, buff, 1);
}
/**
 * @brief  xl_usr_offset_y: [set] Accelerometer Y-axis user offset
 *                                calibration expressed in 2’s complement,
 *                                weight depends on USR_OFF_W in
 *                                CTRL6_C (15h).
 *                                The value must be in the range [-127, +127].
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_xl_usr_offset_y_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_write_reg(ctx, LSM6DSO_Y_OFS_USR, buff, 1);
}

/**
 * @brief  xl_usr_offset_y: [get] Accelerometer Y-axis user offset
 *                                calibration expressed in 2’s complement,
 *                                weight depends on USR_OFF_W
 *                                in CTRL6_C (15h).
 *                                The value must be in the range [-127, +127].
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_xl_usr_offset_y_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_Y_OFS_USR, buff, 1);
}
/**
 * @brief  xl_usr_offset_z: [set] Accelerometer Z-axis user offset
 *                                calibration expressed in 2’s complement,
 *                                weight depends on USR_OFF_W
 *                                in CTRL6_C (15h).
 *                                The value must be in the range [-127, +127].
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_xl_usr_offset_z_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_write_reg(ctx, LSM6DSO_Z_OFS_USR, buff, 1);
}

/**
 * @brief  xl_usr_offset_z: [get] Accelerometer Z-axis user offset
 *                                calibration expressed in 2’s complement,
 *                                weight depends on USR_OFF_W
 *                                in CTRL6_C (15h).
 *                                The value must be in the range [-127, +127].
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_xl_usr_offset_z_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_Z_OFS_USR, buff, 1);
}

/**
 * @brief  xl_usr_offset_out: [set]  Enables user offset on out.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of usr_off_on_out in reg CTRL7_G
 *
 */
int32_t lsm6dso_xl_usr_offset_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);
	reg.ctrl7_g.usr_off_on_out = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_usr_offset_out: [get]  Get user offset on out flag.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: values of usr_off_on_out in reg CTRL7_G
 *
 */
int32_t lsm6dso_xl_usr_offset_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);
	*val = reg.ctrl7_g.usr_off_on_out;

	return mm_error;
}
/**
 * @}
 */

/**
 * @addtogroup  Timestamp
 * @brief   This section groups all the functions that manage the timestamp
 *          generation.
 * @{
 */

/**
 * @brief  timestamp: [set]  Enables timestamp counter.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of timestamp_en in reg CTRL10_C
 *
 */
int32_t lsm6dso_timestamp_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL10_C, &reg.byte, 1);
	reg.ctrl10_c.timestamp_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL10_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  timestamp: [get]  Enables timestamp counter.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of timestamp_en in reg CTRL10_C
 *
 */
int32_t lsm6dso_timestamp_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL10_C, &reg.byte, 1);
	*val = reg.ctrl10_c.timestamp_en;

	return mm_error;
}

/**
 * @brief  timestamp_raw: [get] Timestamp first data output register (r).
 *                              The value is expressed as a 32-bit word
 *                              and the bit resolution is 25 μs.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_timestamp_raw_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_TIMESTAMP0, buff, 4);
}
/**
 * @}
 */

/**
 * @addtogroup  Data output
 * @brief   This section groups all the data output functions.
 * @{
 */

/**
 * @brief  rounding_mode: [set]  Circular burst-mode (rounding) read of
 *                               the output registers.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_rounding_t: change the values of rounding in reg CTRL5_C
 *
 */
int32_t lsm6dso_rounding_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_rounding_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);
	reg.ctrl5_c.rounding = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  rounding_mode: [get]  Gyroscope UI chain full-scale selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_rounding_t: Get the values of rounding in reg CTRL5_C
 *
 */
int32_t lsm6dso_rounding_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_rounding_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);
	*val = (lsm6dso_rounding_t) reg.ctrl5_c.rounding;

	return mm_error;
}

/**
 * @brief  temperature_raw: [get] Temperature data output register (r).
 *                                L and H registers together express a
 *                                16-bit word in two’s complement.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_temperature_raw_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_OUT_TEMP_L, buff, 2);
}
/**
 * @brief  angular_rate_raw: [get] Angular rate sensor.
 *                                 The value is expressed as a 16-bit
 *                                 word in two’s complement.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_angular_rate_raw_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_OUTX_L_G, buff, 6);
}
/**
 * @brief  acceleration_raw: [get] Linear acceleration output register.
 *                                 The value is expressed as a 16-bit word
 *                                 in two’s complement.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_acceleration_raw_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_OUTX_L_A, buff, 6);
}
/**
 * @brief  fifo_out_raw: [get] FIFOdataoutput
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_fifo_out_raw_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_FIFO_DATA_OUT_X_L, buff, 6);
}

/**
 * @brief   emb_number_of_steps: [get]  Step counter output register
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_number_of_steps_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_STEP_COUNTER_L, buff, 2);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @brief   steps_reset: [get]  Reset step counter register
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 *
 */
int32_t lsm6dso_steps_reset(lsm6dso_ctx_t *ctx) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_SRC, &reg.byte, 1);
	reg.emb_func_src.pedo_rst_step = PROPERTY_ENABLE;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_SRC, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @}
 */

/**
 * @addtogroup  common
 * @brief   This section groups common usefull functions.
 * @{
 */

/**
 * @brief  odr_cal_reg: [set] Difference in percentage of the effective ODR
 *                            (and timestamp rate) with respect to the
 *                            typical.
 *                            Step:  0.15%. 8-bit format, 2's complement.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of freq_fine in reg
 *                      INTERNAL_FREQ_FINE
 *
 */
int32_t lsm6dso_odr_cal_reg_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INTERNAL_FREQ_FINE, &reg.byte, 1);
	reg.internal_freq_fine.freq_fine = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INTERNAL_FREQ_FINE, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  odr_cal_reg: [get] Difference in percentage of the effective ODR
 *                            (and timestamp rate) with respect to the
 *                            typical.
 *                            Step:  0.15%. 8-bit format, 2's complement.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of freq_fine in reg INTERNAL_FREQ_FINE
 *
 */
int32_t lsm6dso_odr_cal_reg_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INTERNAL_FREQ_FINE, &reg.byte, 1);
	*val = reg.internal_freq_fine.freq_fine;

	return mm_error;
}

/**
 * @brief  mem_bank: [set] Enable access to the embedded functions/sensor
 *                         hub configuration registers
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_reg_access_t: change the values of reg_access in
 *                               reg FUNC_CFG_ACCESS
 *
 */
int32_t lsm6dso_mem_bank_set(lsm6dso_ctx_t *ctx, lsm6dso_reg_access_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FUNC_CFG_ACCESS, &reg.byte, 1);
	reg.func_cfg_access.reg_access = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FUNC_CFG_ACCESS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  mem_bank: [get] Enable access to the embedded functions/sensor
 *                         hub configuration registers
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_reg_access_t: Get the values of reg_access in
 *                               reg FUNC_CFG_ACCESS
 *
 */
int32_t lsm6dso_mem_bank_get(lsm6dso_ctx_t *ctx, lsm6dso_reg_access_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FUNC_CFG_ACCESS, &reg.byte, 1);
	*val = (lsm6dso_reg_access_t) reg.func_cfg_access.reg_access;

	return mm_error;
}

/**
 * @brief  ln_pg_write_byte: write a line(byte) in a page
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t address: page line address
 * @param  uint8_t val: value to write
 *
 */
int32_t lsm6dso_ln_pg_write_byte(lsm6dso_ctx_t *ctx, uint16_t address, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	reg.page_rw.page_rw = 0x02; /* page_write enable */
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);
	reg.page_sel.page_sel = ((address >> 8) & 0xf);
	reg.page_sel.not_used_01 = 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);
	reg.page_address.page_addr = address & 0xFF;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_ADDRESS, &reg.byte, 1);

	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_VALUE, &val, 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	reg.page_rw.page_rw = 0x00; /* page_write disable */
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  ln_pg_write: write buffer in a page
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t address: page line address
 * @param  uint8_t *buf: buffer to write
 * @param  uint8_t len: buffer len
 *
 */
int32_t lsm6dso_ln_pg_write(lsm6dso_ctx_t *ctx, uint16_t address, uint8_t *buf, uint8_t len) {
	lsm6dso_reg_t reg;
	int32_t mm_error;
	uint8_t msb, lsb;
	uint8_t i;

	msb = ((address >> 8) & 0xf);
	lsb = address & 0xff;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	reg.page_rw.page_rw = 0x02; /* page_write enable*/
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);
	reg.page_sel.page_sel = msb;
	reg.page_sel.not_used_01 = 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);
	reg.page_address.page_addr = lsb;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_ADDRESS, &reg.byte, 1);

	for (i = 0; i < len; i++) {
		mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_VALUE, &buf[i], 1);

		/* Check if page wrap */
		if (++lsb == 0) {
			msb++;
			mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);
			reg.page_sel.page_sel = msb;
			reg.page_sel.not_used_01 = 1;
			mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);
		}
	}

	reg.page_sel.page_sel = 0;
	reg.page_sel.not_used_01 = 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	reg.page_rw.page_rw = 0x00; /* page_write disable */
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  ln_pg_read_byte: read a line(byte) in a page
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t address: page line address
 * @param  uint8_t *val: read value
 *
 */
int32_t lsm6dso_ln_pg_read_byte(lsm6dso_ctx_t *ctx, uint16_t address, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	reg.page_rw.page_rw = 0x01; /* page_read enable*/
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);
	reg.page_sel.page_sel = ((address >> 8) & 0xf);
	reg.page_sel.not_used_01 = 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_SEL, &reg.byte, 1);
	reg.page_address.page_addr = address & 0x00FF;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_ADDRESS, &reg.byte, 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_VALUE, val, 2);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	reg.page_rw.page_rw = 0x00; /* page_read disable */
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  data_ready_mode: [set]   data-ready pulsed / letched mode
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_dataready_pulsed_t: change the values of
 *                                     dataready_pulsed in
 *                                     reg COUNTER_BDR_REG1
 *
 */
int32_t lsm6dso_data_ready_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_dataready_pulsed_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);
	reg.counter_bdr_reg1.dataready_pulsed = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  data_ready_mode: [get]   data-ready pulsed / letched mode
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_dataready_pulsed_t: Get the values of
 *                                     dataready_pulsed in
 *                                     reg COUNTER_BDR_REG1
 *
 */
int32_t lsm6dso_data_ready_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_dataready_pulsed_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);
	*val = (lsm6dso_dataready_pulsed_t) reg.counter_bdr_reg1.dataready_pulsed;

	return mm_error;
}

/**
 * @brief  device_id: [get] DeviceWhoamI.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_device_id_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	return lsm6dso_read_reg(ctx, LSM6DSO_WHO_AM_I, buff, 1);
}
/**
 * @brief  reset: [set] Software reset. Restore the default values
 *                      in user registers
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of sw_reset in reg CTRL3_C
 *
 */
int32_t lsm6dso_reset_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	reg.ctrl3_c.sw_reset = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  reset: [get] Software reset. Restore the default
 *                      values in user registers
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of sw_reset in reg CTRL3_C
 *
 */
int32_t lsm6dso_reset_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	*val = reg.ctrl3_c.sw_reset;

	return mm_error;
}

/**
 * @brief  auto_increment: [set] Register address automatically
 *                               incremented during a multiple byte
 *                               access with a serial interface
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of if_inc in reg CTRL3_C
 *
 */
int32_t lsm6dso_auto_increment_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	reg.ctrl3_c.if_inc = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  auto_increment: [get] Register address automatically
 *                               incremented during a multiple byte
 *                               access with a serial interface
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of if_inc in reg CTRL3_C
 *
 */
int32_t lsm6dso_auto_increment_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	*val = reg.ctrl3_c.if_inc;

	return mm_error;
}

/**
 * @brief  boot: [set] Reboot memory content. Reload the calibration
 *                     parameters.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of boot in reg CTRL3_C
 *
 */
int32_t lsm6dso_boot_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	reg.ctrl3_c.boot = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  boot: [get]  Reboot memory content. Reload the
 *                      calibration parameters.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of boot in reg CTRL3_C
 *
 */
int32_t lsm6dso_boot_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	*val = reg.ctrl3_c.boot;

	return mm_error;
}

/**
 * @brief  xl_self_test: [set]  Linear acceleration sensor self-test enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_xl_t: change the values of st_xl in reg CTRL5_C
 *
 */
int32_t lsm6dso_xl_self_test_set(lsm6dso_ctx_t *ctx, lsm6dso_st_xl_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);
	reg.ctrl5_c.st_xl = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_self_test: [get]  Linear acceleration sensor self-test enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_xl_t: Get the values of st_xl in reg CTRL5_C
 *
 */
int32_t lsm6dso_xl_self_test_get(lsm6dso_ctx_t *ctx, lsm6dso_st_xl_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);
	*val = (lsm6dso_st_xl_t) reg.ctrl5_c.st_xl;

	return mm_error;
}

/**
 * @brief  gy_self_test: [set]  Angular rate sensor self-test enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_g_t: change the values of st_g in reg CTRL5_C
 *
 */
int32_t lsm6dso_gy_self_test_set(lsm6dso_ctx_t *ctx, lsm6dso_st_g_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);
	reg.ctrl5_c.st_g = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  gy_self_test: [get]  Angular rate sensor self-test enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_g_t: Get the values of st_g in reg CTRL5_C
 *
 */
int32_t lsm6dso_gy_self_test_get(lsm6dso_ctx_t *ctx, lsm6dso_st_g_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL5_C, &reg.byte, 1);
	*val = (lsm6dso_st_g_t) reg.ctrl5_c.st_g;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  filters
 * @brief   This section group all the functions concerning the
 *          filters configuration
 * @{
 */

/**
 * @brief  xl_filter_lp2: [set] accelerometer output from LPF2
 *                              filtering stage selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of lpf2_xl_en in reg CTRL1_XL
 *
 */
int32_t lsm6dso_xl_filter_lp2_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);
	reg.ctrl1_xl.lpf2_xl_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_filter_lp2: [get] accelerometer output from LPF2
 *                              filtering stage selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of lpf2_xl_en in reg CTRL1_XL
 *
 */
int32_t lsm6dso_xl_filter_lp2_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_XL, &reg.byte, 1);
	*val = reg.ctrl1_xl.lpf2_xl_en;

	return mm_error;
}

/**
 * @brief  gy_filter_lp1: [set] Enables gyroscope digital LPF1 if
 *                              auxiliary SPI is disabled; the bandwidth
 *                              can be selected through FTYPE [2:0]
 *                              in CTRL6_C (15h).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of lpf1_sel_g in reg CTRL4_C
 *
 */
int32_t lsm6dso_gy_filter_lp1_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	reg.ctrl4_c.lpf1_sel_g = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  gy_filter_lp1: [get] Enables gyroscope digital LPF1 if auxiliary
 *                              SPI is disabled; the bandwidth can be
 *                              selected through FTYPE [2:0] in CTRL6_C (15h).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of lpf1_sel_g in reg CTRL4_C
 *
 */
int32_t lsm6dso_gy_filter_lp1_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	*val = reg.ctrl4_c.lpf1_sel_g;

	return mm_error;
}

/**
 * @brief   filter_settling_mask: [set] Mask DRDY on pin (both XL & Gyro)
 *                                      until filter settling ends
 *                                      (XL and Gyro independently masked).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of drdy_mask in reg CTRL4_C
 *
 */
int32_t lsm6dso_filter_settling_mask_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	reg.ctrl4_c.drdy_mask = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   filter_settling_mask: [get] Mask DRDY on pin (both XL & Gyro)
 *                                      until filter settling ends
 *                                      (XL and Gyro independently masked).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of drdy_mask in reg CTRL4_C
 *
 */
int32_t lsm6dso_filter_settling_mask_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	*val = reg.ctrl4_c.drdy_mask;

	return mm_error;
}

/**
 * @brief  gy_lp1_bandwidth: [set]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ftype_t: change the values of ftype in reg CTRL6_C
 *
 */
int32_t lsm6dso_gy_lp1_bandwidth_set(lsm6dso_ctx_t *ctx, lsm6dso_ftype_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);
	reg.ctrl6_c.ftype = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  gy_lp1_bandwidth: [get]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ftype_t: Get the values of ftype in reg CTRL6_C
 *
 */
int32_t lsm6dso_gy_lp1_bandwidth_get(lsm6dso_ctx_t *ctx, lsm6dso_ftype_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);
	*val = (lsm6dso_ftype_t) reg.ctrl6_c.ftype;

	return mm_error;
}

/**
 * @brief  xl_lp2_on_6d: [set]  Low pass filter 2 on 6D function selection.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of low_pass_on_6d in reg CTRL8_XL
 *
 */
int32_t lsm6dso_xl_lp2_on_6d_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);
	reg.ctrl8_xl.low_pass_on_6d = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_lp2_on_6d: [get]  Low pass filter 2 on 6D function selection.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of low_pass_on_6d in reg CTRL8_XL
 *
 */
int32_t lsm6dso_xl_lp2_on_6d_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);
	*val = reg.ctrl8_xl.low_pass_on_6d;

	return mm_error;
}

/**
 * @brief  xl_hp_path_on_out: [set] Accelerometer slope filter /
 *                                  high-pass filter selection on output.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_hp_slope_xl_en_t: change the values of hp_slope_xl_en
 *                                   in reg CTRL8_XL
 *
 */
int32_t lsm6dso_xl_hp_path_on_out_set(lsm6dso_ctx_t *ctx, lsm6dso_hp_slope_xl_en_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);
	reg.ctrl8_xl.hp_slope_xl_en = (val & 0x10) >> 4;
	reg.ctrl8_xl.hp_ref_mode_xl = (val & 0x20) >> 5;
	reg.ctrl8_xl.hpcf_xl = val & 0x07;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_hp_path_on_out: [get] Accelerometer slope filter /
 *                                  high-pass filter selection on output.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_hp_slope_xl_en_t: Get the values of hp_slope_xl_en
 *                                   in reg CTRL8_XL
 *
 */
int32_t lsm6dso_xl_hp_path_on_out_get(lsm6dso_ctx_t *ctx, lsm6dso_hp_slope_xl_en_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);
	*val = (lsm6dso_hp_slope_xl_en_t) ((reg.ctrl8_xl.hp_ref_mode_xl << 5) + (reg.ctrl8_xl.hp_slope_xl_en << 4) + reg.ctrl8_xl.hpcf_xl);

	return mm_error;
}

/**
 * @brief  xl_fast_settling: [set] Enables accelerometer LPF2 and
 *                                 HPF fast-settling mode. The filter sets
 *                                 the second samples after writing this bit.
 *                                 Active only during device exit from
 *                                 powerdown mode.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of fastsettl_mode_xl in
 *                      reg CTRL8_XL
 *
 */
int32_t lsm6dso_xl_fast_settling_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);
	reg.ctrl8_xl.fastsettl_mode_xl = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  xl_fast_settling: [get] Enables accelerometer LPF2 and
 *                                 HPF fast-settling mode. The filter
 *                                 sets the second samples after writing
 *                                 this bit. Active only during device
 *                                 exit from powerdown mode.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of fastsettl_mode_xl in reg CTRL8_XL
 *
 */
int32_t lsm6dso_xl_fast_settling_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);
	*val = reg.ctrl8_xl.fastsettl_mode_xl;

	return mm_error;
}

/**
 * @brief   xl_hp_path_internal: [set] HPF or SLOPE filter selection on
 *                                     wake-up and Activity/Inactivity
 *                                     functions.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_slope_fds_t: change the values of slope_fds in reg TAP_CFG0
 *
 */
int32_t lsm6dso_xl_hp_path_internal_set(lsm6dso_ctx_t *ctx, lsm6dso_slope_fds_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	reg.tap_cfg0.slope_fds = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   xl_hp_path_internal: [get] HPF or SLOPE filter selection on
 *                                     wake-up and Activity/Inactivity
 *                                     functions.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_slope_fds_t: Get the values of slope_fds in reg TAP_CFG0
 *
 */
int32_t lsm6dso_xl_hp_path_internal_get(lsm6dso_ctx_t *ctx, lsm6dso_slope_fds_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	*val = (lsm6dso_slope_fds_t) reg.tap_cfg0.slope_fds;

	return mm_error;
}

/**
 * @brief   gy_hp_path_internal: [set] Enables gyroscope digital high-pass
 *                                     filter. The filter is enabled only
 *                                     if the gyro is in HP mode.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_hpm_g_t: Get the values of hp_en_g and hp_en_g
 *                            in reg CTRL7_G
 *
 */
int32_t lsm6dso_gy_hp_path_internal_set(lsm6dso_ctx_t *ctx, lsm6dso_hpm_g_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);
	reg.ctrl7_g.hp_en_g = (val & 0x80) >> 7;
	reg.ctrl7_g.hpm_g = val & 0x03;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   gy_hp_path_internal: [get] Enables gyroscope digital high-pass
 *                                     filter. The filter is enabled only
 *                                     if the gyro is in HP mode.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_hpm_g_t: Get the values of hp_en_g and hp_en_g
 *                            in reg CTRL7_G
 *
 */
int32_t lsm6dso_gy_hp_path_internal_get(lsm6dso_ctx_t *ctx, lsm6dso_hpm_g_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);
	*val = (lsm6dso_hpm_g_t) ((reg.ctrl7_g.hp_en_g << 7) + reg.ctrl7_g.hpm_g);

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup   Auxiliary_interface
 * @brief   This section groups all the functions concerning
 *          auxiliary interface.
 * @{
 */

/**
 * @brief  aux_sdo_ocs_mode: [set] On auxiliary interface
 *                                 connect/disconnect SDO and OCS
 *                                 internal pull-up.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ois_pu_dis_t: change the values of ois_pu_dis in
 *                               reg PIN_CTRL
 *
 */
int32_t lsm6dso_aux_sdo_ocs_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_ois_pu_dis_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PIN_CTRL, &reg.byte, 1);
	reg.pin_ctrl.ois_pu_dis = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PIN_CTRL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_sdo_ocs_mode: [get] On auxiliary interface
 *                                 connect/disconnect SDO and OCS
 *                                 internal pull-up.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ois_pu_dis_t: Get the values of ois_pu_dis in reg PIN_CTRL
 *
 */
int32_t lsm6dso_aux_sdo_ocs_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_ois_pu_dis_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PIN_CTRL, &reg.byte, 1);
	*val = (lsm6dso_ois_pu_dis_t) reg.pin_ctrl.ois_pu_dis;

	return mm_error;
}

/**
 * @brief  aux_pw_on_ctrl: [set]  OIS chain on aux interface power on mode
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ois_on_t: change the values of ois_on in reg CTRL7_G
 *
 */
int32_t lsm6dso_aux_pw_on_ctrl_set(lsm6dso_ctx_t *ctx, lsm6dso_ois_on_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);
	reg.ctrl7_g.ois_on_en = val & 0x01;
	reg.ctrl7_g.ois_on = val & 0x01;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_pw_on_ctrl: [get]  OIS chain on aux interface power on mode
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ois_on_t: Get the values of ois_on in reg CTRL7_G
 *
 */
int32_t lsm6dso_aux_pw_on_ctrl_get(lsm6dso_ctx_t *ctx, lsm6dso_ois_on_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL7_G, &reg.byte, 1);
	*val = (lsm6dso_ois_on_t) reg.ctrl7_g.ois_on;

	return mm_error;
}

/**
 * @brief  aux_xl_full_scale: [set] Accelerometer full-scale management
 *                                  between UI chain and OIS chain.
 *                                  When XL UI is on, the full scale is
 *                                  the same between UI/OIS and is chosen
 *                                  by the UI CTRL registers;
 *                                  when XL UI is in PD, the OIS can
 *                                  choose the FS. Full scales are
 *                                  independent between the UI/OIS chain
 *                                  but both bound to 8 g.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_xl_fs_mode_t: change the values of xl_fs_mode in
 *                               reg CTRL8_XL
 *
 */
int32_t lsm6dso_aux_xl_fs_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_xl_fs_mode_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);
	reg.ctrl8_xl.xl_fs_mode = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_xl_full_scale: [get] Accelerometer full-scale management
 *                                  between UI chain and OIS chain.
 *                                  When XL UI is on, the full scale is
 *                                  the same between UI/OIS and is chosen
 *                                  by the UI CTRL registers; when XL UI
 *                                  is in PD, the OIS can choose the FS.
 *                                  Full scales are independent between the
 *                                  UI/OIS chain but both bound to 8 g.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_xl_fs_mode_t: Get the values of xl_fs_mode in reg CTRL8_XL
 *
 */
int32_t lsm6dso_aux_xl_fs_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_xl_fs_mode_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL8_XL, &reg.byte, 1);
	*val = (lsm6dso_xl_fs_mode_t) reg.ctrl8_xl.xl_fs_mode;

	return mm_error;
}

/**
 * @brief  aux_status_reg: [get] The STATUS_SPIAux register is read by
 *                               the auxiliary SPI.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_status_spiaux_t: registers STATUS_SPIAUX
 *
 */
int32_t lsm6dso_aux_status_reg_get(lsm6dso_ctx_t *ctx, lsm6dso_status_spiaux_t *val) {
	return lsm6dso_read_reg(ctx, LSM6DSO_STATUS_SPIAUX, (uint8_t*) val, 1);
}
/**
 * @brief   aux_xl_flag_data_ready: [get]  AUX accelerometer data available
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of xlda in reg STATUS_SPIAUX
 *
 */
int32_t lsm6dso_aux_xl_flag_data_ready_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_STATUS_SPIAUX, &reg.byte, 1);
	*val = reg.status_spiaux.xlda;

	return mm_error;
}
/**
 * @brief   aux_gy_flag_data_ready: [get]  AUX gyroscope data available.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of gda in reg STATUS_SPIAUX
 *
 */
int32_t lsm6dso_aux_gy_flag_data_ready_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_STATUS_SPIAUX, &reg.byte, 1);
	*val = reg.status_spiaux.gda;

	return mm_error;
}
/**
 * @brief   aux_gy_flag_settling: [get] High when the gyroscope output
 *                                      is in the settling phase.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of gyro_settling in reg STATUS_SPIAUX
 *
 */
int32_t lsm6dso_aux_gy_flag_settling_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_STATUS_SPIAUX, &reg.byte, 1);
	*val = reg.status_spiaux.gyro_settling;

	return mm_error;
}
/**
 * @brief  aux_xl_self_test: [set] Selects accelerometer self-test.
 *                                 Effective only if XL OIS chain is enabled.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_xl_ois_t: change the values of st_xl_ois in reg INT_OIS
 *
 */
int32_t lsm6dso_aux_xl_self_test_set(lsm6dso_ctx_t *ctx, lsm6dso_st_xl_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);
	reg.int_ois.st_xl_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_xl_self_test: [get] Selects accelerometer self-test.
 *                                 Effective only if XL OIS chain is enabled.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_xl_ois_t: Get the values of st_xl_ois in reg INT_OIS
 *
 */
int32_t lsm6dso_aux_xl_self_test_get(lsm6dso_ctx_t *ctx, lsm6dso_st_xl_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);
	*val = (lsm6dso_st_xl_ois_t) reg.int_ois.st_xl_ois;

	return mm_error;
}

/**
 * @brief  aux_den_polarity: [set] Indicates polarity of DEN signal
 *                                 on OIS chain
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_den_lh_ois_t: change the values of den_lh_ois in
 *                               reg INT_OIS
 *
 */
int32_t lsm6dso_aux_den_polarity_set(lsm6dso_ctx_t *ctx, lsm6dso_den_lh_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);
	reg.int_ois.den_lh_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_den_polarity: [get] Indicates polarity of DEN signal on
 *                                 OIS chain
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_den_lh_ois_t: Get the values of den_lh_ois in reg INT_OIS
 *
 */
int32_t lsm6dso_aux_den_polarity_get(lsm6dso_ctx_t *ctx, lsm6dso_den_lh_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);
	*val = (lsm6dso_den_lh_ois_t) reg.int_ois.den_lh_ois;

	return mm_error;
}

/**
 * @brief  aux_den_mode: [set]  Configure DEN mode on the OIS chain
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_lvl2_ois_t: change the values of lvl2_ois in reg INT_OIS
 *
 */
int32_t lsm6dso_aux_den_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_lvl2_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);
	reg.int_ois.lvl2_ois = val & 0x01;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);
	reg.ctrl1_ois.lvl1_ois = (val & 0x02) >> 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_den_mode: [get]  Configure DEN mode on the OIS chain
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_lvl2_ois_t: Get the values of lvl2_ois in reg INT_OIS
 *
 */
int32_t lsm6dso_aux_den_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_lvl2_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);
	*val = (lsm6dso_lvl2_ois_t) ((reg.ctrl1_ois.lvl1_ois << 1) + reg.int_ois.lvl2_ois);

	return mm_error;
}

/**
 * @brief  aux_drdy_on_int2: [set] Enables/Disable OIS chain DRDY on
 *                                 INT2 pin. This setting has priority
 *                                 over all other INT2 settings.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of int2_drdy_ois in reg INT_OIS
 *
 */
int32_t lsm6dso_aux_drdy_on_int2_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);
	reg.int_ois.int2_drdy_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_drdy_on_int2: [get] Enables/Disable OIS chain DRDY on
 *                                 INT2 pin. This setting has priority
 *                                 over all other INT2 settings.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of int2_drdy_ois in reg INT_OIS
 *
 */
int32_t lsm6dso_aux_drdy_on_int2_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_OIS, &reg.byte, 1);
	*val = reg.int_ois.int2_drdy_ois;

	return mm_error;
}

/**
 * @brief  aux_mode: [set] Enables OIS chain data processing for gyro in
 *                         Mode 3 and Mode 4 (mode4_en = 1) and
 *                         accelerometer data in and Mode 4 (mode4_en = 1).
 *                         When the OIS chain is enabled, the OIS outputs
 *                         are available through the SPI2 in registers
 *                         OUTX_L_G (22h) through OUTZ_H_G (27h) and
 *                         STATUS_REG (1Eh) / STATUS_SPIAux, and
 *                         LPF1 is dedicated to this chain.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ois_en_spi2_t: change the values of ois_en_spi2 in
 *                                reg CTRL1_OIS
 *
 */
int32_t lsm6dso_aux_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_ois_en_spi2_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);
	reg.ctrl1_ois.ois_en_spi2 = val & 0x01;
	reg.ctrl1_ois.mode4_en = (val & 0x02) >> 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_mode: [get] Enables OIS chain data processing for gyro in
 *                         Mode 3 and Mode 4 (mode4_en = 1) and accelerometer
 *                         data in and Mode 4 (mode4_en = 1).
 *                         When the OIS chain is enabled, the OIS outputs
 *                         are available through the SPI2 in registers
 *                         OUTX_L_G (22h) through OUTZ_H_G (27h) and
 *                         STATUS_REG (1Eh) / STATUS_SPIAux, and
 *                         LPF1 is dedicated to this chain.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ois_en_spi2_t: Get the values of ois_en_spi2 in
 *                                reg CTRL1_OIS
 *
 */
int32_t lsm6dso_aux_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_ois_en_spi2_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);
	*val = (lsm6dso_ois_en_spi2_t) ((reg.ctrl1_ois.mode4_en << 1) + reg.ctrl1_ois.ois_en_spi2);

	return mm_error;
}

/**
 * @brief  aux_gy_full_scale: [set]  Selects gyroscope OIS chain full-scale.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fs_g_ois_t: change the values of fs_g_ois in reg CTRL1_OIS
 *
 */
int32_t lsm6dso_aux_gy_full_scale_set(lsm6dso_ctx_t *ctx, lsm6dso_fs_g_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);
	reg.ctrl1_ois.fs_g_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_gy_full_scale: [get]  Selects gyroscope OIS chain full-scale.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fs_g_ois_t: Get the values of fs_g_ois in reg CTRL1_OIS
 *
 */
int32_t lsm6dso_aux_gy_full_scale_get(lsm6dso_ctx_t *ctx, lsm6dso_fs_g_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);
	*val = (lsm6dso_fs_g_ois_t) reg.ctrl1_ois.fs_g_ois;

	return mm_error;
}

/**
 * @brief  aux_spi_mode: [set]  SPI2 3- or 4-wire interface.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sim_ois_t: change the values of sim_ois in reg CTRL1_OIS
 *
 */
int32_t lsm6dso_aux_spi_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_sim_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);
	reg.ctrl1_ois.sim_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_spi_mode: [get]  SPI2 3- or 4-wire interface.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sim_ois_t: Get the values of sim_ois in reg CTRL1_OIS
 *
 */
int32_t lsm6dso_aux_spi_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_sim_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL1_OIS, &reg.byte, 1);
	*val = (lsm6dso_sim_ois_t) reg.ctrl1_ois.sim_ois;

	return mm_error;
}

/**
 * @brief   aux_gy_lp1_bandwidth: [set] Selects gyroscope digital
 *                                      LPF1 filter bandwidth.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ftype_ois_t: change the values of ftype_ois in
 *                              reg CTRL2_OIS
 *
 */
int32_t lsm6dso_aux_gy_lp1_bandwidth_set(lsm6dso_ctx_t *ctx, lsm6dso_ftype_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL2_OIS, &reg.byte, 1);
	reg.ctrl2_ois.ftype_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL2_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   aux_gy_lp1_bandwidth: [get] Selects gyroscope digital LPF1
 *                                      filter bandwidth.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ftype_ois_t: Get the values of ftype_ois in reg CTRL2_OIS
 *
 */
int32_t lsm6dso_aux_gy_lp1_bandwidth_get(lsm6dso_ctx_t *ctx, lsm6dso_ftype_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL2_OIS, &reg.byte, 1);
	*val = (lsm6dso_ftype_ois_t) reg.ctrl2_ois.ftype_ois;

	return mm_error;
}

/**
 * @brief   aux_gy_hp_bandwidth: [set] Selects gyroscope OIS chain
 *                                     digital high-pass filter cutoff.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_hpm_ois_t: change the values of hpm_ois in reg CTRL2_OIS
 *
 */
int32_t lsm6dso_aux_gy_hp_bandwidth_set(lsm6dso_ctx_t *ctx, lsm6dso_hpm_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL2_OIS, &reg.byte, 1);
	reg.ctrl2_ois.hpm_ois = val & 0x03;
	reg.ctrl2_ois.hp_en_ois = (val & 0x10) >> 4;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL2_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   aux_gy_hp_bandwidth: [get] Selects gyroscope OIS chain
 *                                     digital high-pass filter cutoff.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_hpm_ois_t: Get the values of hpm_ois in reg CTRL2_OIS
 *
 */
int32_t lsm6dso_aux_gy_hp_bandwidth_get(lsm6dso_ctx_t *ctx, lsm6dso_hpm_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL2_OIS, &reg.byte, 1);
	*val = (lsm6dso_hpm_ois_t) ((reg.ctrl2_ois.hp_en_ois << 4) + reg.ctrl2_ois.hpm_ois);

	return mm_error;
}

/**
 * @brief  aux_gy_clamp: [set] Enable / Disables OIS chain clamp.
 *                             Enable: All OIS chain outputs = 8000h
 *                             during self-test; Disable: OIS chain self-test
 *                             outputs dependent from the aux gyro full
 *                             scale selected.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_ois_clampdis_t: change the values of st_ois_clampdis in
 *                                    reg CTRL3_OIS
 *
 */
int32_t lsm6dso_aux_gy_clamp_set(lsm6dso_ctx_t *ctx, lsm6dso_st_ois_clampdis_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);
	reg.ctrl3_ois.st_ois_clampdis = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_gy_clamp: [get] Enable / Disables OIS chain clamp.
 *                             Enable: All OIS chain outputs = 8000h
 *                             during self-test; Disable: OIS chain
 *                             self-test outputs dependent from the aux
 *                             gyro full scale selected.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_ois_clampdis_t: Get the values of st_ois_clampdis in
 *                                    reg CTRL3_OIS
 *
 */
int32_t lsm6dso_aux_gy_clamp_get(lsm6dso_ctx_t *ctx, lsm6dso_st_ois_clampdis_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);
	*val = (lsm6dso_st_ois_clampdis_t) reg.ctrl3_ois.st_ois_clampdis;

	return mm_error;
}

/**
 * @brief  aux_gy_self_test: [set]  Selects gyroscope OIS chain self-test.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_ois_t: change the values of st_ois in reg CTRL3_OIS
 *
 */
int32_t lsm6dso_aux_gy_self_test_set(lsm6dso_ctx_t *ctx, lsm6dso_st_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);
	reg.ctrl3_ois.st_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_gy_self_test: [get] Selects gyroscope OIS chain self-test.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_st_ois_t: Get the values of st_ois in reg CTRL3_OIS
 *
 */
int32_t lsm6dso_aux_gy_self_test_get(lsm6dso_ctx_t *ctx, lsm6dso_st_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);
	*val = (lsm6dso_st_ois_t) reg.ctrl3_ois.st_ois;

	return mm_error;
}

/**
 * @brief  aux_xl_bandwidth: [set] Selects accelerometer OIS channel
 *                                 bandwidth.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_filter_xl_conf_ois_t: change the values of
 *                                       filter_xl_conf_ois in reg CTRL3_OIS
 *
 */
int32_t lsm6dso_aux_xl_bandwidth_set(lsm6dso_ctx_t *ctx, lsm6dso_filter_xl_conf_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);
	reg.ctrl3_ois.filter_xl_conf_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_xl_bandwidth: [get] Selects accelerometer OIS
 *                                 channel bandwidth.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_filter_xl_conf_ois_t: Get the values of
 *                                       filter_xl_conf_ois in reg CTRL3_OIS
 *
 */
int32_t lsm6dso_aux_xl_bandwidth_get(lsm6dso_ctx_t *ctx, lsm6dso_filter_xl_conf_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);
	*val = (lsm6dso_filter_xl_conf_ois_t) reg.ctrl3_ois.filter_xl_conf_ois;

	return mm_error;
}

/**
 * @brief  aux_xl_full_scale: [set] Selects accelerometer OIS
 *                                  channel full-scale.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fs_xl_ois_t: change the values of fs_xl_ois in
 *                              reg CTRL3_OIS
 *
 */
int32_t lsm6dso_aux_xl_full_scale_set(lsm6dso_ctx_t *ctx, lsm6dso_fs_xl_ois_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);
	reg.ctrl3_ois.fs_xl_ois = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  aux_xl_full_scale: [get] Selects accelerometer OIS channel
 *                                  full-scale.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fs_xl_ois_t: Get the values of fs_xl_ois in reg CTRL3_OIS
 *
 */
int32_t lsm6dso_aux_xl_full_scale_get(lsm6dso_ctx_t *ctx, lsm6dso_fs_xl_ois_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_OIS, &reg.byte, 1);
	*val = (lsm6dso_fs_xl_ois_t) reg.ctrl3_ois.fs_xl_ois;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup   main_serial_interface
 * @brief   This section groups all the functions concerning main
 *          serial interface management (not auxiliary)
 * @{
 */

/**
 * @brief  sdo_sa0_mode: [set]  Connect/Disconnect SDO/SA0 internal pull-up.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sdo_pu_en_t: change the values of sdo_pu_en in
 *                              reg PIN_CTRL
 *
 */
int32_t lsm6dso_sdo_sa0_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_sdo_pu_en_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PIN_CTRL, &reg.byte, 1);
	reg.pin_ctrl.sdo_pu_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PIN_CTRL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  sdo_sa0_mode: [get]  Connect/Disconnect SDO/SA0 internal pull-up.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sdo_pu_en_t: Get the values of sdo_pu_en in reg PIN_CTRL
 *
 */
int32_t lsm6dso_sdo_sa0_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_sdo_pu_en_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PIN_CTRL, &reg.byte, 1);
	*val = (lsm6dso_sdo_pu_en_t) reg.pin_ctrl.sdo_pu_en;

	return mm_error;
}

/**
 * @brief  spi_mode: [set]  SPI Serial Interface Mode selection.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sim_t: change the values of sim in reg CTRL3_C
 *
 */
int32_t lsm6dso_spi_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_sim_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	reg.ctrl3_c.sim = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  spi_mode: [get]  SPI Serial Interface Mode selection.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sim_t: Get the values of sim in reg CTRL3_C
 *
 */
int32_t lsm6dso_spi_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_sim_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	*val = (lsm6dso_sim_t) reg.ctrl3_c.sim;

	return mm_error;
}

/**
 * @brief  i2c_interface: [set]  Disable / Enable I2C interface.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_i2c_disable_t: change the values of i2c_disable in
 *                                reg CTRL4_C
 *
 */
int32_t lsm6dso_i2c_interface_set(lsm6dso_ctx_t *ctx, lsm6dso_i2c_disable_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	reg.ctrl4_c.i2c_disable = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  i2c_interface: [get]  Disable / Enable I2C interface.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_i2c_disable_t: Get the values of i2c_disable in
 *                                reg CTRL4_C
 *
 */
int32_t lsm6dso_i2c_interface_get(lsm6dso_ctx_t *ctx, lsm6dso_i2c_disable_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	*val = (lsm6dso_i2c_disable_t) reg.ctrl4_c.i2c_disable;

	return mm_error;
}

/**
 * @brief  i3c_disable: [set]  I3C Enable/Disable communication protocol
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_i3c_disable_t val: change the values of i3c_disable
 *                                    in reg CTRL9_XL
 *
 */
int32_t lsm6dso_i3c_disable_set(lsm6dso_ctx_t *ctx, lsm6dso_i3c_disable_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	reg.ctrl9_xl.i3c_disable = (val & 0x80) >> 7;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_I3C_BUS_AVB, &reg.byte, 1);
	reg.i3c_bus_avb.i3c_bus_avb_sel = val & 0x03;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_I3C_BUS_AVB, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  i3c_disable: [get]  I3C Enable/Disable communication protocol
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_i3c_disable_t: change the values of i3c_disable in
 *                                reg CTRL9_XL
 *
 */
int32_t lsm6dso_i3c_disable_get(lsm6dso_ctx_t *ctx, lsm6dso_i3c_disable_t *val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg[0].byte, 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_I3C_BUS_AVB, &reg[1].byte, 1);

	*val = (lsm6dso_i3c_disable_t) ((reg[0].ctrl9_xl.i3c_disable << 7) + reg[1].i3c_bus_avb.i3c_bus_avb_sel);

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  interrupt_pins
 * @brief   This section groups all the functions that manage interrup pins
 * @{
 */

/**
 * @brief  pin_int1_route: [set] Select the signal that need to route on
 *                               int1 pad
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_pin_int1_route: union of registers: INT1_CTRL,
 *                                 MD1_CFG, EMB_FUNC_INT1, FSM_INT1_A,
 *                                 FSM_INT1_B
 *
 */
int32_t lsm6dso_pin_int1_route_set(lsm6dso_ctx_t *ctx, lsm6dso_pin_int1_route_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_INT1, &val->byte[2], 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FSM_INT1_A, &val->byte[3], 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FSM_INT1_B, &val->byte[4], 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	if (val->byte[2] || val->byte[3] || val->byte[4]) {
		val->reg.md1_cfg.int1_emb_func = PROPERTY_ENABLE;
	} else {
		val->reg.md1_cfg.int1_emb_func = PROPERTY_DISABLE;
	}

	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT1_CTRL, &val->byte[0], 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MD1_CFG, &val->byte[1], 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);

	if (val->byte[0] || val->reg.md1_cfg.int1_6d || val->reg.md1_cfg.int1_double_tap || val->reg.md1_cfg.int1_ff || val->reg.md1_cfg.int1_wu || val->reg.md1_cfg.int1_single_tap || val->reg.md1_cfg.int1_sleep_change) {
		reg.tap_cfg2.interrupts_enable = PROPERTY_ENABLE;
	} else {
		reg.tap_cfg2.interrupts_enable = PROPERTY_DISABLE;
	}
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  pin_int1_route: [get] Select the signal that need to route on
 *                               int1 pad
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_pin_int1_route: union of registers: INT1_CTRL, MD1_CFG,
 *                                 EMB_FUNC_INT1, FSM_INT1_A, FSM_INT1_B
 *
 */
int32_t lsm6dso_pin_int1_route_get(lsm6dso_ctx_t *ctx, lsm6dso_pin_int1_route_t *val) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_INT1, &val->byte[2], 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_INT1_A, &val->byte[3], 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_INT1_B, &val->byte[4], 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT1_CTRL, &val->byte[0], 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MD1_CFG, &val->byte[1], 1);
	return mm_error;
}
/**
 * @brief  pin_int2_route: [set] Select the signal that need to route on
 *                               int2 pad
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_pin_int2_route: union of registers INT2_CTRL,  MD2_CFG,
 *                                 EMB_FUNC_INT2, FSM_INT2_A, FSM_INT2_B
 *
 */
int32_t lsm6dso_pin_int2_route_set(lsm6dso_ctx_t *ctx, lsm6dso_pin_int2_route_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_INT2, &val->byte[2], 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FSM_INT2_A, &val->byte[3], 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FSM_INT2_B, &val->byte[4], 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	if (val->byte[2] || val->byte[3] || val->byte[4]) {
		val->reg.md2_cfg.int2_emb_func = PROPERTY_ENABLE;
	} else {
		val->reg.md2_cfg.int2_emb_func = PROPERTY_DISABLE;
	}

	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT2_CTRL, &val->byte[0], 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MD2_CFG, &val->byte[1], 1);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);
	if (val->byte[0] || val->reg.md2_cfg.int2_6d || val->reg.md2_cfg.int2_double_tap || val->reg.md2_cfg.int2_ff || val->reg.md2_cfg.int2_wu || val->reg.md2_cfg.int2_single_tap || val->reg.md2_cfg.int2_sleep_change) {
		reg.tap_cfg2.interrupts_enable = PROPERTY_ENABLE;
	} else {
		reg.tap_cfg2.interrupts_enable = PROPERTY_DISABLE;
	}
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  pin_int2_route: [get] Select the signal that need to route on
 *                               int2 pad
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_pin_int2_route: union of registers INT2_CTRL,  MD2_CFG,
 *                                 EMB_FUNC_INT2, FSM_INT2_A, FSM_INT2_B
 *
 */
int32_t lsm6dso_pin_int2_route_get(lsm6dso_ctx_t *ctx, lsm6dso_pin_int2_route_t *val) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_INT2, &val->byte[2], 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_INT2_A, &val->byte[3], 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_INT2_B, &val->byte[4], 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT2_CTRL, &val->byte[0], 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MD2_CFG, &val->byte[1], 1);

	return mm_error;
}
/**
 * @brief  pin_mode: [set]  Push-pull/open drain selection on interrupt pads.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_pp_od_t: change the values of pp_od in reg CTRL3_C
 *
 */
int32_t lsm6dso_pin_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_pp_od_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	reg.ctrl3_c.pp_od = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  pin_mode: [get]  Push-pull/open drain selection on interrupt pads.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_pp_od_t: Get the values of pp_od in reg CTRL3_C
 *
 */
int32_t lsm6dso_pin_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_pp_od_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	*val = (lsm6dso_pp_od_t) reg.ctrl3_c.pp_od;

	return mm_error;
}

/**
 * @brief  pin_polarity: [set]  Interrupt active-high/low.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_h_lactive_t: change the values of h_lactive in reg CTRL3_C
 *
 */
int32_t lsm6dso_pin_polarity_set(lsm6dso_ctx_t *ctx, lsm6dso_h_lactive_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	reg.ctrl3_c.h_lactive = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  pin_polarity: [get]  Interrupt active-high/low.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_h_lactive_t: Get the values of h_lactive in reg CTRL3_C
 *
 */
int32_t lsm6dso_pin_polarity_get(lsm6dso_ctx_t *ctx, lsm6dso_h_lactive_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL3_C, &reg.byte, 1);
	*val = (lsm6dso_h_lactive_t) reg.ctrl3_c.h_lactive;

	return mm_error;
}

/**
 * @brief  all_on_int1: [set] All interrupt signals become available on
 *                            INT1 pin.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of int2_on_int1 in reg CTRL4_C
 *
 */
int32_t lsm6dso_all_on_int1_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	reg.ctrl4_c.int2_on_int1 = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  all_on_int1: [get] All interrupt signals become available on
 *                            INT1 pin.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of int2_on_int1 in reg CTRL4_C
 *
 */
int32_t lsm6dso_all_on_int1_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	*val = reg.ctrl4_c.int2_on_int1;

	return mm_error;
}

/**
 * @brief  int_notification: [set]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_lir_t: change the values of lir in reg TAP_CFG0
 *
 */
int32_t lsm6dso_int_notification_set(lsm6dso_ctx_t *ctx, lsm6dso_lir_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	reg.tap_cfg0.lir = val & 0x01;
	reg.tap_cfg0.int_clr_on_read = val & 0x01;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	reg.page_rw.emb_func_lir = (val & 0x02) >> 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  int_notification: [get]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_lir_t: Get the values of lir in reg TAP_CFG0
 *
 */
int32_t lsm6dso_int_notification_get(lsm6dso_ctx_t *ctx, lsm6dso_lir_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	*val = (lsm6dso_lir_t) 0;
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	*val = (lsm6dso_lir_t) reg.tap_cfg0.lir;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_PAGE_RW, &reg.byte, 1);
	*val |= (lsm6dso_lir_t) (reg.page_rw.emb_func_lir << 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  Wake_Up_event
 * @brief   This section groups all the functions that manage the Wake Up
 *          event generation.
 * @{
 */

/**
 * @brief  wkup_ths_weight: [set] Weight of 1 LSB of wakeup threshold.
 *                                0: 1 LSB =FS_XL  /  64
 *                                1: 1 LSB = FS_XL / 256
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_wake_ths_w_t: change the values of wake_ths_w in
 *                                 reg WAKE_UP_DUR
 *
 */
int32_t lsm6dso_wkup_ths_weight_set(lsm6dso_ctx_t *ctx, lsm6dso_wake_ths_w_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);
	reg.wake_up_dur.wake_ths_w = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  wkup_ths_weight: [get] Weight of 1 LSB of wakeup threshold.
 *                                0: 1 LSB =FS_XL  /  64
 *                                1: 1 LSB = FS_XL / 256
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_wake_ths_w_t: Get the values of wake_ths_w in
 *                                 reg WAKE_UP_DUR
 *
 */
int32_t lsm6dso_wkup_ths_weight_get(lsm6dso_ctx_t *ctx, lsm6dso_wake_ths_w_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);
	*val = (lsm6dso_wake_ths_w_t) reg.wake_up_dur.wake_ths_w;

	return mm_error;
}

/**
 * @brief  wkup_threshold: [set] Threshold for wakeup: 1 LSB weight depends
 *                               on WAKE_THS_W in WAKE_UP_DUR.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of wk_ths in reg WAKE_UP_THS
 *
 */
int32_t lsm6dso_wkup_threshold_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);
	reg.wake_up_ths.wk_ths = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  wkup_threshold: [get] Threshold for wakeup: 1 LSB weight depends
 *                               on WAKE_THS_W in WAKE_UP_DUR.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of wk_ths in reg WAKE_UP_THS
 *
 */
int32_t lsm6dso_wkup_threshold_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);
	*val = reg.wake_up_ths.wk_ths;

	return mm_error;
}

/**
 * @brief   xl_usr_offset_on_wkup: [set] Wake up duration event.
 *                                       1LSb = 1 / ODR
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of usr_off_on_wu in reg WAKE_UP_THS
 *
 */
int32_t lsm6dso_xl_usr_offset_on_wkup_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);
	reg.wake_up_ths.usr_off_on_wu = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   xl_usr_offset_on_wkup: [get] Wake up duration event.
 *                                       1LSb = 1 / ODR
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of usr_off_on_wu in reg WAKE_UP_THS
 *
 */
int32_t lsm6dso_xl_usr_offset_on_wkup_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);
	*val = reg.wake_up_ths.usr_off_on_wu;

	return mm_error;
}

/**
 * @brief  wkup_dur: [set]  Wake up duration event.1LSb = 1 / ODR
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of wake_dur in reg WAKE_UP_DUR
 *
 */
int32_t lsm6dso_wkup_dur_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);
	reg.wake_up_dur.wake_dur = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  wkup_dur: [get]  Wake up duration event.1LSb = 1 / ODR
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of wake_dur in reg WAKE_UP_DUR
 *
 */
int32_t lsm6dso_wkup_dur_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);
	*val = reg.wake_up_dur.wake_dur;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup   Activity/Inactivity_detection
 * @brief   This section groups all the functions concerning
 *          activity/inactivity detection.
 * @{
 */

/**
 * @brief  gy_sleep_mode: [set]  Enables gyroscope Sleep mode.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of sleep_g in reg CTRL4_C
 *
 */
int32_t lsm6dso_gy_sleep_mode_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	reg.ctrl4_c.sleep_g = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  gy_sleep_mode: [get]  Enables gyroscope Sleep mode.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of sleep_g in reg CTRL4_C
 *
 */
int32_t lsm6dso_gy_sleep_mode_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL4_C, &reg.byte, 1);
	*val = reg.ctrl4_c.sleep_g;

	return mm_error;
}

/**
 * @brief   act_pin_notification: [set] Drives the sleep status instead of
 *                                      sleep change on INT pins
 *                                      (only if INT1_SLEEP_CHANGE or
 *                                      INT2_SLEEP_CHANGE bits are enabled).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sleep_status_on_int_t: change the values of
 *                                        sleep_status_on_int in reg TAP_CFG0
 *
 */
int32_t lsm6dso_act_pin_notification_set(lsm6dso_ctx_t *ctx, lsm6dso_sleep_status_on_int_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	reg.tap_cfg0.sleep_status_on_int = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   act_pin_notification: [get] Drives the sleep status instead of
 *                                      sleep change on INT pins (only if
 *                                      INT1_SLEEP_CHANGE or
 *                                      INT2_SLEEP_CHANGE bits are enabled).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sleep_status_on_int_t: Get the values of
 *                                        sleep_status_on_int in reg TAP_CFG0
 *
 */
int32_t lsm6dso_act_pin_notification_get(lsm6dso_ctx_t *ctx, lsm6dso_sleep_status_on_int_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	*val = (lsm6dso_sleep_status_on_int_t) reg.tap_cfg0.sleep_status_on_int;

	return mm_error;
}

/**
 * @brief  act_mode: [set]  Enable inactivity function.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_inact_en_t: change the values of inact_en in reg TAP_CFG2
 *
 */
int32_t lsm6dso_act_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_inact_en_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);
	reg.tap_cfg2.inact_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  act_mode: [get]  Enable inactivity function.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_inact_en_t: Get the values of inact_en in reg TAP_CFG2
 *
 */
int32_t lsm6dso_act_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_inact_en_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);
	*val = (lsm6dso_inact_en_t) reg.tap_cfg2.inact_en;

	return mm_error;
}

/**
 * @brief  act_sleep_dur: [set] Duration to go in sleep mode.
 *                              1 LSb = 512 / ODR
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of sleep_dur in reg WAKE_UP_DUR
 *
 */
int32_t lsm6dso_act_sleep_dur_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);
	reg.wake_up_dur.sleep_dur = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  act_sleep_dur: [get] Duration to go in sleep mode.
 *                              1 LSb = 512 / ODR
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of sleep_dur in reg WAKE_UP_DUR
 *
 */
int32_t lsm6dso_act_sleep_dur_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg.byte, 1);
	*val = reg.wake_up_dur.sleep_dur;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  tap_generator
 * @brief   This section groups all the functions that manage the
 *          tap and double tap event generation.
 * @{
 */

/**
 * @brief  tap_detection_on_z: [set]  Enable Z direction in tap recognition.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of tap_z_en in reg TAP_CFG0
 *
 */
int32_t lsm6dso_tap_detection_on_z_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	reg.tap_cfg0.tap_z_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_detection_on_z: [get]  Enable Z direction in tap recognition.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tap_z_en in reg TAP_CFG0
 *
 */
int32_t lsm6dso_tap_detection_on_z_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	*val = reg.tap_cfg0.tap_z_en;

	return mm_error;
}

/**
 * @brief  tap_detection_on_y: [set]  Enable Y direction in tap recognition.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of tap_y_en in reg TAP_CFG0
 *
 */
int32_t lsm6dso_tap_detection_on_y_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	reg.tap_cfg0.tap_y_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_detection_on_y: [get]  Enable Y direction in tap recognition.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tap_y_en in reg TAP_CFG0
 *
 */
int32_t lsm6dso_tap_detection_on_y_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	*val = reg.tap_cfg0.tap_y_en;

	return mm_error;
}

/**
 * @brief  tap_detection_on_x: [set]  Enable X direction in tap recognition.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of tap_x_en in reg TAP_CFG0
 *
 */
int32_t lsm6dso_tap_detection_on_x_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	reg.tap_cfg0.tap_x_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_detection_on_x: [get]  Enable X direction in tap recognition.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tap_x_en in reg TAP_CFG0
 *
 */
int32_t lsm6dso_tap_detection_on_x_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG0, &reg.byte, 1);
	*val = reg.tap_cfg0.tap_x_en;

	return mm_error;
}

/**
 * @brief  tap_threshold_x: [set]  X-axis tap recognition threshold.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of tap_ths_x in reg TAP_CFG1
 *
 */
int32_t lsm6dso_tap_threshold_x_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG1, &reg.byte, 1);
	reg.tap_cfg1.tap_ths_x = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG1, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_threshold_x: [get]  X-axis tap recognition threshold.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tap_ths_x in reg TAP_CFG1
 *
 */
int32_t lsm6dso_tap_threshold_x_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG1, &reg.byte, 1);
	*val = reg.tap_cfg1.tap_ths_x;

	return mm_error;
}

/**
 * @brief  tap_axis_priority: [set] Selection of axis priority for TAP
 *                                  detection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_tap_priority_t: change the values of tap_priority in
 *                                 reg TAP_CFG1
 *
 */
int32_t lsm6dso_tap_axis_priority_set(lsm6dso_ctx_t *ctx, lsm6dso_tap_priority_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG1, &reg.byte, 1);
	reg.tap_cfg1.tap_priority = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG1, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_axis_priority: [get] Selection of axis priority for TAP
 *                                  detection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_tap_priority_t: Get the values of tap_priority in
 *                                 reg TAP_CFG1
 *
 */
int32_t lsm6dso_tap_axis_priority_get(lsm6dso_ctx_t *ctx, lsm6dso_tap_priority_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG1, &reg.byte, 1);
	*val = (lsm6dso_tap_priority_t) reg.tap_cfg1.tap_priority;

	return mm_error;
}

/**
 * @brief  tap_threshold_y: [set]  Y-axis tap recognition threshold.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of tap_ths_y in reg TAP_CFG2
 *
 */
int32_t lsm6dso_tap_threshold_y_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);
	reg.tap_cfg2.tap_ths_y = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_threshold_y: [get]  Y-axis tap recognition threshold.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tap_ths_y in reg TAP_CFG2
 *
 */
int32_t lsm6dso_tap_threshold_y_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_CFG2, &reg.byte, 1);
	*val = reg.tap_cfg2.tap_ths_y;

	return mm_error;
}

/**
 * @brief  tap_threshold_z: [set]  Z-axis recognition threshold.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of tap_ths_z in reg TAP_THS_6D
 *
 */
int32_t lsm6dso_tap_threshold_z_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);
	reg.tap_ths_6d.tap_ths_z = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_threshold_z: [get]  Z-axis recognition threshold.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tap_ths_z in reg TAP_THS_6D
 *
 */
int32_t lsm6dso_tap_threshold_z_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);
	*val = reg.tap_ths_6d.tap_ths_z;

	return mm_error;
}

/**
 * @brief  tap_shock: [set] Maximum duration is the maximum time of an
 *                          overthreshold signal detection to be recognized
 *                          as a tap event. The default value of these bits
 *                          is 00b which corresponds to 4*ODR_XL time.
 *                          If the SHOCK[1:0] bits are set to a different
 *                          value, 1LSB corresponds to 8*ODR_XL time.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of shock in reg INT_DUR2
 *
 */
int32_t lsm6dso_tap_shock_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);
	reg.int_dur2.shock = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_shock: [get] Maximum duration is the maximum time of an
 *                          overthreshold signal detection to be recognized
 *                          as a tap event. The default value of these bits
 *                          is 00b which corresponds to 4*ODR_XL time.
 *                          If the SHOCK[1:0] bits are set to a different
 *                          value, 1LSB corresponds to 8*ODR_XL time.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of shock in reg INT_DUR2
 *
 */
int32_t lsm6dso_tap_shock_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);
	*val = reg.int_dur2.shock;

	return mm_error;
}

/**
 * @brief  tap_quiet: [set] Quiet time is the time after the first detected
 *                          tap in which there must not be any overthreshold
 *                          event.
 *                          The default value of these bits is 00b which
 *                          corresponds to 2*ODR_XL time. If the QUIET[1:0]
 *                          bits are set to a different value,
 *                          1LSB corresponds to 4*ODR_XL time.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of quiet in reg INT_DUR2
 *
 */
int32_t lsm6dso_tap_quiet_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);
	reg.int_dur2.quiet = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_quiet: [get] Quiet time is the time after the first detected
 *                          tap in which there must not be any overthreshold
 *                          event.
 *                          The default value of these bits is 00b which
 *                          corresponds to 2*ODR_XL time.
 *                          If the QUIET[1:0] bits are set to a different
 *                          value, 1LSB corresponds to 4*ODR_XL time.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of quiet in reg INT_DUR2
 *
 */
int32_t lsm6dso_tap_quiet_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);
	*val = reg.int_dur2.quiet;

	return mm_error;
}

/**
 * @brief  tap_dur: [set] When double tap recognition is enabled,
 *                        this register expresses the maximum time
 *                        between two consecutive detected taps to
 *                        determine a double tap event.
 *                        The default value of these bits is 0000b which
 *                        corresponds to 16*ODR_XL time.
 *                        If the DUR[3:0] bits are set to a different value,
 *                        1LSB corresponds to 32*ODR_XL time.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of dur in reg INT_DUR2
 *
 */
int32_t lsm6dso_tap_dur_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);
	reg.int_dur2.dur = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_dur: [get] When double tap recognition is enabled,
 *                        this register expresses the maximum time
 *                        between two consecutive detected taps to
 *                        determine a double tap event.
 *                        The default value of these bits is 0000b which
 *                        corresponds to 16*ODR_XL time. If the DUR[3:0]
 *                        bits are set to a different value,
 *                        1LSB corresponds to 32*ODR_XL time.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of dur in reg INT_DUR2
 *
 */
int32_t lsm6dso_tap_dur_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_INT_DUR2, &reg.byte, 1);
	*val = reg.int_dur2.dur;

	return mm_error;
}

/**
 * @brief  tap_mode: [set]  Single/double-tap event enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_single_double_tap_t: change the values of
 *                                      single_double_tap in reg WAKE_UP_THS
 *
 */
int32_t lsm6dso_tap_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_single_double_tap_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);
	reg.wake_up_ths.single_double_tap = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  tap_mode: [get]  Single/double-tap event enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_single_double_tap_t: Get the values of
 *                                      single_double_tap in reg WAKE_UP_THS
 *
 */
int32_t lsm6dso_tap_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_single_double_tap_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_THS, &reg.byte, 1);
	*val = (lsm6dso_single_double_tap_t) reg.wake_up_ths.single_double_tap;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup   Six_position_detection(6D/4D)
 * @brief   This section groups all the functions concerning six position
 *          detection (6D).
 * @{
 */

/**
 * @brief  6d_threshold: [set]  Threshold for 4D/6D function.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sixd_ths_t: change the values of sixd_ths in
 *                             reg TAP_THS_6D
 *
 */
int32_t lsm6dso_6d_threshold_set(lsm6dso_ctx_t *ctx, lsm6dso_sixd_ths_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);
	reg.tap_ths_6d.sixd_ths = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  6d_threshold: [get]  Threshold for 4D/6D function.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sixd_ths_t: Get the values of sixd_ths in reg TAP_THS_6D
 *
 */
int32_t lsm6dso_6d_threshold_get(lsm6dso_ctx_t *ctx, lsm6dso_sixd_ths_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);
	*val = (lsm6dso_sixd_ths_t) reg.tap_ths_6d.sixd_ths;

	return mm_error;
}

/**
 * @brief  4d_mode: [set]  4D orientation detection enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of d4d_en in reg TAP_THS_6D
 *
 */
int32_t lsm6dso_4d_mode_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);
	reg.tap_ths_6d.d4d_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  4d_mode: [get]  4D orientation detection enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of d4d_en in reg TAP_THS_6D
 *
 */
int32_t lsm6dso_4d_mode_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_TAP_THS_6D, &reg.byte, 1);
	*val = reg.tap_ths_6d.d4d_en;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  free_fall
 * @brief   This section group all the functions concerning the free
 *          fall detection.
 * @{
 */
/**
 * @brief  ff_threshold: [set]  Free fall threshold setting.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ff_ths_t: change the values of ff_ths in reg FREE_FALL
 *
 */
int32_t lsm6dso_ff_threshold_set(lsm6dso_ctx_t *ctx, lsm6dso_ff_ths_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FREE_FALL, &reg.byte, 1);
	reg.free_fall.ff_ths = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FREE_FALL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  ff_threshold: [get]  Free fall threshold setting.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_ff_ths_t: Get the values of ff_ths in reg FREE_FALL
 *
 */
int32_t lsm6dso_ff_threshold_get(lsm6dso_ctx_t *ctx, lsm6dso_ff_ths_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FREE_FALL, &reg.byte, 1);
	*val = (lsm6dso_ff_ths_t) reg.free_fall.ff_ths;

	return mm_error;
}

/**
 * @brief  ff_dur: [set]  Free-fall duration event. 1LSb = 1 / ODR
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of ff_dur in reg FREE_FALL
 *
 */
int32_t lsm6dso_ff_dur_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg[0].byte, 2);
	reg[0].wake_up_dur.ff_dur = (val & 0x20) >> 5;
	reg[1].free_fall.ff_dur = val & 0x1F;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg[0].byte, 2);

	return mm_error;
}

/**
 * @brief  ff_dur: [get]  Free-fall duration event. 1LSb = 1 / ODR
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of ff_dur in reg FREE_FALL
 *
 */
int32_t lsm6dso_ff_dur_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_WAKE_UP_DUR, &reg[0].byte, 2);
	*val = (reg[0].wake_up_dur.ff_dur << 5) + reg[1].free_fall.ff_dur;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  fifo
 * @brief   This section group all the functions concerning the fifo usage
 * @{
 */

/**
 * @brief  fifo_watermark: [set]  FIFO watermark level selection.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of wtm in reg FIFO_CTRL1
 *
 */
int32_t lsm6dso_fifo_watermark_set(lsm6dso_ctx_t *ctx, uint16_t val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg[1].byte, 1);
	reg[0].fifo_ctrl1.wtm = 0x00FF & val;
	reg[1].fifo_ctrl2.wtm = (0x0100 & val) >> 8;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL1, &reg[0].byte, 2);

	return mm_error;
}

/**
 * @brief  fifo_watermark: [get]  FIFO watermark level selection.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of wtm in reg FIFO_CTRL1
 *
 */
int32_t lsm6dso_fifo_watermark_get(lsm6dso_ctx_t *ctx, uint16_t *val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL1, &reg[0].byte, 2);
	*val = (reg[1].fifo_ctrl2.wtm << 8) + reg[0].fifo_ctrl1.wtm;

	return mm_error;
}

/**
 * @brief  FIFO compression feature initialization request [set].
 *
 * @param  *ctx      read / write interface definitions
 * @param  val       change the values of FIFO_COMPR_INIT in
 *                   reg EMB_FUNC_INIT_B
 *
 */
int32_t lsm6dso_compression_algo_init_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_INIT_B, &reg.byte, 1);
	reg.emb_func_init_b.fifo_compr_init = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_INIT_B, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  FIFO compression feature initialization request [get].
 *
 * @param  *ctx   read / write interface definitions
 * @param  val    change the values of FIFO_COMPR_INIT in
 *                reg EMB_FUNC_INIT_B
 *
 */
int32_t lsm6dso_compression_algo_init_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_INIT_B, &reg.byte, 1);
	*val = reg.emb_func_init_b.fifo_compr_init;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  compression_algo: [set]  Enable and configure compression algo
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_uncoptr_rate_t: change the values of uncoptr_rate in
 *                                 reg FIFO_CTRL2
 *
 */
int32_t lsm6dso_compression_algo_set(lsm6dso_ctx_t *ctx, lsm6dso_uncoptr_rate_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_B, &reg.byte, 1);
	reg.emb_func_en_b.fifo_compr_en = (val & 0x04) >> 2;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_EN_B, &reg.byte, 1);
	lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);
	reg.fifo_ctrl2.fifo_compr_rt_en = (val & 0x04) >> 2;
	reg.fifo_ctrl2.uncoptr_rate = val & 0x03;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  compression_algo: [get]  Enable and configure compression algo
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_uncoptr_rate_t: Get the values of uncoptr_rate in
 *                                 reg FIFO_CTRL2
 *
 */
int32_t lsm6dso_compression_algo_get(lsm6dso_ctx_t *ctx, lsm6dso_uncoptr_rate_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	*val = (lsm6dso_uncoptr_rate_t) 0;
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);
	*val = (lsm6dso_uncoptr_rate_t) reg.fifo_ctrl2.uncoptr_rate;
	*val |= (lsm6dso_uncoptr_rate_t) reg.fifo_ctrl2.fifo_compr_rt_en << 2;

	return mm_error;
}

/**
 * @brief   fifo_virtual_sens_odr_chg: [set] Enables ODR CHANGE virtual
 *                                           sensor to be batched in FIFO
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of odrchg_en in reg FIFO_CTRL2
 *
 */
int32_t lsm6dso_fifo_virtual_sens_odr_chg_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);
	reg.fifo_ctrl2.odrchg_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   fifo_virtual_sens_odr_chg: [get] Enables ODR CHANGE virtual
 *                                           sensor to be batched in FIFO
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of odrchg_en in reg FIFO_CTRL2
 *
 */
int32_t lsm6dso_fifo_virtual_sens_odr_chg_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);
	*val = reg.fifo_ctrl2.odrchg_en;

	return mm_error;
}

/**
 * @brief   compression_algo_real_time: [set] Enables/Disables
 *                                            compression algorithm runtime
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of fifo_compr_rt_en in
 *                      reg FIFO_CTRL2
 *
 */
int32_t lsm6dso_compression_algo_real_time_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);
	reg.fifo_ctrl2.fifo_compr_rt_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   compression_algo_real_time: [get] Enables/Disables compression
 *                                            algorithm runtime
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of fifo_compr_rt_en in reg FIFO_CTRL2
 *
 */
int32_t lsm6dso_compression_algo_real_time_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);
	*val = reg.fifo_ctrl2.fifo_compr_rt_en;

	return mm_error;
}

/**
 * @brief  fifo_stop_on_wtm: [set] Sensing chain FIFO stop values
 *                                 memorization at threshold level
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of stop_on_wtm in reg FIFO_CTRL2
 *
 */
int32_t lsm6dso_fifo_stop_on_wtm_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);
	reg.fifo_ctrl2.stop_on_wtm = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  fifo_stop_on_wtm: [get] Sensing chain FIFO stop values
 *                                 memorization at threshold level
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of stop_on_wtm in reg FIFO_CTRL2
 *
 */
int32_t lsm6dso_fifo_stop_on_wtm_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL2, &reg.byte, 1);
	*val = reg.fifo_ctrl2.stop_on_wtm;

	return mm_error;
}

/**
 * @brief  fifo_xl_batch: [set] Selects Batching Data Rate (writing
 *                              frequency in FIFO) for accelerometer data.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_bdr_xl_t: change the values of bdr_xl in reg FIFO_CTRL3
 *
 */
int32_t lsm6dso_fifo_xl_batch_set(lsm6dso_ctx_t *ctx, lsm6dso_bdr_xl_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL3, &reg.byte, 1);
	reg.fifo_ctrl3.bdr_xl = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL3, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  fifo_xl_batch: [get] Selects Batching Data Rate
 *                              (writing frequency in FIFO)
 *                              for accelerometer data.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_bdr_xl_t: Get the values of bdr_xl in reg FIFO_CTRL3
 *
 */
int32_t lsm6dso_fifo_xl_batch_get(lsm6dso_ctx_t *ctx, lsm6dso_bdr_xl_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL3, &reg.byte, 1);
	*val = (lsm6dso_bdr_xl_t) reg.fifo_ctrl3.bdr_xl;

	return mm_error;
}

/**
 * @brief  fifo_gy_batch: [set] Selects Batching Data Rate (writing
 *                              frequency in FIFO) for gyroscope data.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_bdr_gy_t: change the values of bdr_gy in reg FIFO_CTRL3
 *
 */
int32_t lsm6dso_fifo_gy_batch_set(lsm6dso_ctx_t *ctx, lsm6dso_bdr_gy_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL3, &reg.byte, 1);
	reg.fifo_ctrl3.bdr_gy = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL3, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  fifo_gy_batch: [get]  Selects Batching Data Rate
 *                               (writing frequency in FIFO)
 *                               for gyroscope data.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_bdr_gy_t: Get the values of bdr_gy in reg FIFO_CTRL3
 *
 */
int32_t lsm6dso_fifo_gy_batch_get(lsm6dso_ctx_t *ctx, lsm6dso_bdr_gy_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL3, &reg.byte, 1);
	*val = (lsm6dso_bdr_gy_t) reg.fifo_ctrl3.bdr_gy;

	return mm_error;
}

/**
 * @brief  fifo_mode: [set]  FIFO mode selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fifo_mode_t: change the values of fifo_mode in
 *                              reg FIFO_CTRL4
 *
 */
int32_t lsm6dso_fifo_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_fifo_mode_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);
	reg.fifo_ctrl4.fifo_mode = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  fifo_mode: [get]  FIFO mode selection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fifo_mode_t: Get the values of fifo_mode in reg FIFO_CTRL4
 *
 */
int32_t lsm6dso_fifo_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_fifo_mode_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);
	*val = (lsm6dso_fifo_mode_t) reg.fifo_ctrl4.fifo_mode;

	return mm_error;
}

/**
 * @brief  fifo_temp_batch: [set] Selects Batching Data Rate (writing
 *                                frequency in FIFO) for temperature data
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_odr_t_batch_t: change the values of odr_t_batch in
 *                                reg FIFO_CTRL4
 *
 */
int32_t lsm6dso_fifo_temp_batch_set(lsm6dso_ctx_t *ctx, lsm6dso_odr_t_batch_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);
	reg.fifo_ctrl4.odr_t_batch = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  fifo_temp_batch: [get] Selects Batching Data Rate
 *                                (writing frequency in FIFO)
 *                                for temperature data
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_odr_t_batch_t: Get the values of odr_t_batch in
 *                                reg FIFO_CTRL4
 *
 */
int32_t lsm6dso_fifo_temp_batch_get(lsm6dso_ctx_t *ctx, lsm6dso_odr_t_batch_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);
	*val = (lsm6dso_odr_t_batch_t) reg.fifo_ctrl4.odr_t_batch;

	return mm_error;
}

/**
 * @brief   fifo_timestamp_decimation: [set] Selects decimation for
 *                                           timestamp batching in FIFO.
 *                                           Writing rate will be the
 *                                           maximum rate between XL and
 *                                           GYRO BDR divided by decimation
 *                                           decoder.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_odr_ts_batch_t: change the values of odr_ts_batch in
 *                                 reg FIFO_CTRL4
 *
 */
int32_t lsm6dso_fifo_timestamp_decimation_set(lsm6dso_ctx_t *ctx, lsm6dso_odr_ts_batch_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);
	reg.fifo_ctrl4.odr_ts_batch = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   fifo_timestamp_decimation: [get] Selects decimation for
 *                                           timestamp batching in FIFO.
 *                                           Writing rate will be the
 *                                           maximum rate between XL and
 *                                           GYRO BDR divided by decimation
 *                                           decoder.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_odr_ts_batch_t: Get the values of odr_ts_batch in reg
 *                                 FIFO_CTRL4
 *
 */
int32_t lsm6dso_fifo_timestamp_decimation_get(lsm6dso_ctx_t *ctx, lsm6dso_odr_ts_batch_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_CTRL4, &reg.byte, 1);
	*val = (lsm6dso_odr_ts_batch_t) reg.fifo_ctrl4.odr_ts_batch;

	return mm_error;
}

/**
 * @brief   fifo_cnt_event_batch: [set] Selects the trigger for the
 *                                      internal counter of batching events
 *                                      between XL and gyro.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_trig_counter_bdr_t: change the values of trig_counter_bdr
 *                                     in reg COUNTER_BDR_REG1
 *
 */
int32_t lsm6dso_fifo_cnt_event_batch_set(lsm6dso_ctx_t *ctx, lsm6dso_trig_counter_bdr_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);
	reg.counter_bdr_reg1.trig_counter_bdr = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief   fifo_cnt_event_batch: [get] Selects the trigger for the internal
 *                                      counter of batching events between XL
 *                                      and gyro.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_trig_counter_bdr_t: Get the values of trig_counter_bdr
 *                                     in reg COUNTER_BDR_REG1
 *
 */
int32_t lsm6dso_fifo_cnt_event_batch_get(lsm6dso_ctx_t *ctx, lsm6dso_trig_counter_bdr_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);
	*val = (lsm6dso_trig_counter_bdr_t) reg.counter_bdr_reg1.trig_counter_bdr;

	return mm_error;
}

/**
 * @brief  rst_batch_counter: [set] Resets the internal counter of batching
 *                                  events for a single sensor.
 *                                  This bit is automatically reset to
 *                                  zero if it was set to ‘1’.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of rst_counter_bdr in
 *                      reg COUNTER_BDR_REG1
 *
 */
int32_t lsm6dso_rst_batch_counter_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);
	reg.counter_bdr_reg1.rst_counter_bdr = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  rst_batch_counter: [get] Resets the internal counter of
 *                                  batching events for a single sensor.
 *                                  This bit is automatically reset to zero
 *                                  if it was set to ‘1’.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of rst_counter_bdr in
 *                  reg COUNTER_BDR_REG1
 *
 */
int32_t lsm6dso_rst_batch_counter_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg.byte, 1);
	*val = reg.counter_bdr_reg1.rst_counter_bdr;

	return mm_error;
}

/**
 * @brief   batch_counter_threshold: [set]  Batch data rate counter
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of cnt_bdr_th in
 *                      reg COUNTER_BDR_REG2 and COUNTER_BDR_REG1.
 *
 */
int32_t lsm6dso_batch_counter_threshold_set(lsm6dso_ctx_t *ctx, uint16_t val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg[0].byte, 1);
	reg[1].counter_bdr_reg2.cnt_bdr_th = 0x00FF & val;
	reg[0].counter_bdr_reg1.cnt_bdr_th = (0x0700 & val) >> 8;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg[0].byte, 2);

	return mm_error;
}

/**
 * @brief   batch_counter_threshold: [get]  Batch data rate counter
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of cnt_bdr_th in
 *                  reg COUNTER_BDR_REG2 and COUNTER_BDR_REG1.
 *
 */
int32_t lsm6dso_batch_counter_threshold_get(lsm6dso_ctx_t *ctx, uint16_t *val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_COUNTER_BDR_REG1, &reg[0].byte, 2);
	*val = (reg[0].counter_bdr_reg1.cnt_bdr_th << 8) + reg[1].counter_bdr_reg2.cnt_bdr_th;

	return mm_error;
}

/**
 * @brief  fifo_data_level: [get] Number of unread sensor data
 *                                (TAG + 6 bytes) stored in FIFO
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of diff_fifo in reg FIFO_STATUS1
 *
 */
int32_t lsm6dso_fifo_data_level_get(lsm6dso_ctx_t *ctx, uint16_t *val) {
	lsm6dso_reg_t reg[2];
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_STATUS1, &(reg[0].byte), 2);
	*val = (reg[1].fifo_status2.diff_fifo << 8) + reg[0].fifo_status1.diff_fifo;

	return mm_error;
}
/**
 * @brief  fifo_status: [get]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fifo_status2_t: registers FIFO_STATUS2
 *
 */
int32_t lsm6dso_fifo_status_get(lsm6dso_ctx_t *ctx, lsm6dso_fifo_status2_t *val) {
	return lsm6dso_read_reg(ctx, LSM6DSO_FIFO_STATUS2, (uint8_t*) val, 1);
}
/**
 * @brief  fifo_full_flag: [get]  Smart FIFO full status.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of fifo_full_ia in reg FIFO_STATUS2
 *
 */
int32_t lsm6dso_fifo_full_flag_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_STATUS2, &reg.byte, 1);
	*val = reg.fifo_status2.fifo_full_ia;

	return mm_error;
}
/**
 * @brief  fifo_ovr_flag: [get]  FIFO overrun status.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of  fifo_over_run_latched in
 *                  reg FIFO_STATUS2
 *
 */
int32_t lsm6dso_fifo_ovr_flag_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_STATUS2, &reg.byte, 1);
	*val = reg.fifo_status2.fifo_ovr_ia;

	return mm_error;
}
/**
 * @brief  fifo_wtm_flag: [get]  FIFO watermark status.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of fifo_wtm_ia in reg FIFO_STATUS2
 *
 */
int32_t lsm6dso_fifo_wtm_flag_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_STATUS2, &reg.byte, 1);
	*val = reg.fifo_status2.fifo_wtm_ia;

	return mm_error;
}
/**
 * @brief  fifo_sensor_tag: [get]  Identifies the sensor in FIFO_DATA_OUT.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tag_sensor in reg FIFO_DATA_OUT_TAG
 *
 */
int32_t lsm6dso_fifo_sensor_tag_get(lsm6dso_ctx_t *ctx, lsm6dso_fifo_tag_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FIFO_DATA_OUT_TAG, &reg.byte, 1);
	*val = (lsm6dso_fifo_tag_t) reg.fifo_data_out_tag.tag_sensor;

	return mm_error;
}

/**
 * @brief  lsm6dso_fifo_pedo_batch_set: [set] Enable FIFO batching of
 *                                     pedometer embedded function values.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of gbias_fifo_en in
 *                      reg LSM6DSO_EMB_FUNC_FIFO_CFG
 *
 */
int32_t lsm6dso_fifo_pedo_batch_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_FIFO_CFG, &reg.byte, 1);
	reg.emb_func_fifo_cfg.pedo_fifo_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_FIFO_CFG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  lsm6dso_fifo_pedo_batch_get: [get] Enable FIFO batching of
 *                                     pedometer embedded function values.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of pedo_fifo_en in reg LSM6DSO_EMB_FUNC_FIFO_CFG
 *
 */
int32_t lsm6dso_fifo_pedo_batch_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_FIFO_CFG, &reg.byte, 1);
	*val = reg.emb_func_fifo_cfg.pedo_fifo_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_sh_batch_slave_0: [set] Enable FIFO batching data of
 *                                      first slave.
 *
 * @param  lsm6dso_ctx_t *ctx: write interface definitions
 * @param  uint8_t val: change the values of  batch_ext_sens_0_en in
 *                      reg SLV0_CONFIG
 *
 */
int32_t lsm6dso_sh_batch_slave_0_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV0_CONFIG, &reg.byte, 1);
	reg.slv0_config.batch_ext_sens_0_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV0_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_sh_batch_slave_0: [get] Enable FIFO batching data of
 *                                      first slave.
 *
 * @param  lsm6dso_ctx_t *ctx: read interface definitions
 * @param  uint8_t: change the values of  batch_ext_sens_0_en in
 *                  reg SLV0_CONFIG
 *
 */
int32_t lsm6dso_sh_batch_slave_0_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV0_CONFIG, &reg.byte, 1);
	*val = reg.slv0_config.batch_ext_sens_0_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_sh_batch_slave_1: [set] Enable FIFO batching data of
 *                                      second slave.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of  batch_ext_sens_1_en in
 *                      reg SLV1_CONFIG
 *
 */
int32_t lsm6dso_sh_batch_slave_1_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV1_CONFIG, &reg.byte, 1);
	reg.slv1_config.batch_ext_sens_1_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV1_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_sh_batch_slave_1: [get] Enable FIFO batching data of
 *                                      second slave.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of  batch_ext_sens_1_en in
 *                  reg SLV1_CONFIG
 *
 */
int32_t lsm6dso_sh_batch_slave_1_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV1_CONFIG, &reg.byte, 1);
	*val = reg.slv1_config.batch_ext_sens_1_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_sh_batch_slave_2: [set] Enable FIFO batching data of
 *                                      third slave.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of  batch_ext_sens_2_en in
 *                      reg SLV2_CONFIG
 *
 */
int32_t lsm6dso_sh_batch_slave_2_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV2_CONFIG, &reg.byte, 1);
	reg.slv2_config.batch_ext_sens_2_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV2_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_sh_batch_slave_2: [get] Enable FIFO batching data of
 *                                      third slave.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of  batch_ext_sens_2_en in
 *                  reg SLV2_CONFIG
 *
 */
int32_t lsm6dso_sh_batch_slave_2_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV2_CONFIG, &reg.byte, 1);
	*val = reg.slv2_config.batch_ext_sens_2_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_sh_batch_slave_3: [set] Enable FIFO batching data of
 *                                      fourth slave.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of  batch_ext_sens_3_en
 *                      in reg SLV3_CONFIG
 *
 */
int32_t lsm6dso_sh_batch_slave_3_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV3_CONFIG, &reg.byte, 1);
	reg.slv3_config.batch_ext_sens_3_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV3_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_sh_batch_slave_3: [get] Enable FIFO batching data of
 *                                      fourth slave.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of  batch_ext_sens_3_en in
 *                  reg SLV3_CONFIG
 *
 */
int32_t lsm6dso_sh_batch_slave_3_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV3_CONFIG, &reg.byte, 1);
	*val = reg.slv3_config.batch_ext_sens_3_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  DEN_functionality
 * @brief   This section groups all the functions concerning
 *          DEN functionality.
 * @{
 */

/**
 * @brief  den_mode: [set]  DEN functionality marking mode
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_den_mode_t: change the values of den_mode in reg CTRL6_C
 *
 */
int32_t lsm6dso_den_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_den_mode_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);
	reg.ctrl6_c.den_mode = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  den_mode: [get]  DEN functionality marking mode
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_den_mode_t: Get the values of den_mode in reg CTRL6_C
 *
 */
int32_t lsm6dso_den_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_den_mode_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL6_C, &reg.byte, 1);
	*val = (lsm6dso_den_mode_t) reg.ctrl6_c.den_mode;

	return mm_error;
}

/**
 * @brief  den_polarity: [set]  DEN active level configuration.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_den_lh_t: change the values of den_lh in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_polarity_set(lsm6dso_ctx_t *ctx, lsm6dso_den_lh_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	reg.ctrl9_xl.den_lh = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  den_polarity: [get]  DEN active level configuration.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_den_lh_t: Get the values of den_lh in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_polarity_get(lsm6dso_ctx_t *ctx, lsm6dso_den_lh_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	*val = (lsm6dso_den_lh_t) reg.ctrl9_xl.den_lh;

	return mm_error;
}

/**
 * @brief  den_enable: [set]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_den_xl_g_t: change the values of den_xl_g in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_enable_set(lsm6dso_ctx_t *ctx, lsm6dso_den_xl_g_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	reg.ctrl9_xl.den_xl_g = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  den_enable: [get]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_den_xl_g_t: Get the values of den_xl_g in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_enable_get(lsm6dso_ctx_t *ctx, lsm6dso_den_xl_g_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	*val = (lsm6dso_den_xl_g_t) reg.ctrl9_xl.den_xl_g;

	return mm_error;
}

/**
 * @brief  den_mark_axis_x: [set]  DEN value stored in LSB of X-axis.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of den_z in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_mark_axis_x_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	reg.ctrl9_xl.den_z = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  den_mark_axis_x: [get]  DEN value stored in LSB of X-axis.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of den_z in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_mark_axis_x_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	*val = reg.ctrl9_xl.den_z;

	return mm_error;
}

/**
 * @brief  den_mark_axis_y: [set]  DEN value stored in LSB of Y-axis.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of den_y in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_mark_axis_y_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	reg.ctrl9_xl.den_y = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  den_mark_axis_y: [get]  DEN value stored in LSB of Y-axis.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of den_y in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_mark_axis_y_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	*val = reg.ctrl9_xl.den_y;

	return mm_error;
}

/**
 * @brief  den_mark_axis_z: [set]  DEN value stored in LSB of Z-axis.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of den_x in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_mark_axis_z_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	reg.ctrl9_xl.den_x = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);

	return mm_error;
}

/**
 * @brief  den_mark_axis_z: [get]  DEN value stored in LSB of Z-axis.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of den_x in reg CTRL9_XL
 *
 */
int32_t lsm6dso_den_mark_axis_z_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_CTRL9_XL, &reg.byte, 1);
	*val = reg.ctrl9_xl.den_x;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  Pedometer
 * @brief   This section groups all the functions that manage pedometer.
 * @{
 */

/**
 * @brief  emb_pedo_sens: [set]  Enable pedometer algorithm.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of pedo_en in reg EMB_FUNC_EN_A
 *
 */
int32_t lsm6dso_pedo_sens_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	reg.emb_func_en_a.pedo_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_pedo_sens: [get]  Enable pedometer algorithm.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of pedo_en in reg EMB_FUNC_EN_A
 *
 */
int32_t lsm6dso_pedo_sens_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	*val = reg.emb_func_en_a.pedo_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_pedo_step_detect: [get] Interrupt status bit for
 *                                      step detection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of is_step_det in reg EMB_FUNC_STATUS
 *
 */
int32_t lsm6dso_pedo_step_detect_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_STATUS, &reg.byte, 1);
	*val = reg.emb_func_status.is_step_det;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @brief   pedo_debounce_steps: [set] Pedometer debounce configuration
 *                                     register (r/w).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_pedo_debounce_steps_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_PEDO_DEB_STEPS_CONF, *buff);
	return mm_error;
}

/**
 * @brief   pedo_debounce_steps: [get] Pedometer debounce configuration
 *                                     register (r/w).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_pedo_debounce_steps_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_DEB_STEPS_CONF, buff);
	return mm_error;
}
/**
 * @brief   pedo_steps_period: [set] Time period register for step
 *                                   detection on delta time (r/w).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_pedo_steps_period_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_PEDO_SC_DELTAT_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_PEDO_SC_DELTAT_H, *buff);

	return mm_error;
}

/**
 * @brief   pedo_steps_period: [get] Time period register for step
 *                                   detection on delta time (r/w).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_pedo_steps_period_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_SC_DELTAT_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_SC_DELTAT_H, buff);

	return mm_error;
}

/**
 * @brief  pedo_adv_detection: [set]  Enables the advanced detection feature.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of ad_det_en in reg PEDO_CMD_REG
 *
 */
int32_t lsm6dso_pedo_adv_detection_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_CMD_REG, &reg.byte);
	reg.pedo_cmd_reg.ad_det_en = val;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_PEDO_CMD_REG, reg.byte);

	return mm_error;
}

/**
 * @brief  pedo_adv_detection: [get]  Enables the advanced detection feature.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of ad_det_en in reg PEDO_CMD_REG
 *
 */
int32_t lsm6dso_pedo_adv_detection_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_CMD_REG, &reg.byte);
	*val = reg.pedo_cmd_reg.ad_det_en;

	return mm_error;
}

/**
 * @brief  pedo_false_step_rejection: [set] Enables the false-positive
 *                                          rejection feature.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of fp_rejection_en in
 *                      reg PEDO_CMD_REG
 *
 */
int32_t lsm6dso_pedo_false_step_rejection_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_CMD_REG, &reg.byte);
	reg.pedo_cmd_reg.fp_rejection_en = val;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_PEDO_CMD_REG, reg.byte);

	return mm_error;
}

/**
 * @brief  pedo_false_step_rejection: [get] Enables the false-positive
 *                                          rejection feature.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of fp_rejection_en in reg PEDO_CMD_REG
 *
 */
int32_t lsm6dso_pedo_false_step_rejection_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_CMD_REG, &reg.byte);
	*val = reg.pedo_cmd_reg.fp_rejection_en;

	return mm_error;
}

/**
 * @brief  pedo_int_mode: [set] Set when user wants to generate interrupt
 *                              on count overflow event/every step.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_carry_count_en_t: change the values of carry_count_en
 *                                   in reg PEDO_CMD_REG
 *
 */
int32_t lsm6dso_pedo_int_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_carry_count_en_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_CMD_REG, &reg.byte);
	reg.pedo_cmd_reg.carry_count_en = val;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_PEDO_CMD_REG, reg.byte);

	return mm_error;
}

/**
 * @brief  pedo_int_mode: [get] Set when user wants to generate
 *                              interrupt on count overflow event/every step.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_carry_count_en_t: Get the values of carry_count_en in
 *                                   reg PEDO_CMD_REG
 *
 */
int32_t lsm6dso_pedo_int_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_carry_count_en_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_PEDO_CMD_REG, &reg.byte);
	*val = (lsm6dso_carry_count_en_t) reg.pedo_cmd_reg.carry_count_en;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  significant_motion
 * @brief   This section groups all the functions that manage the
 *          significant motion detection.
 * @{
 */

/**
 * @brief  emb_motion_sens: [set] Enable significant motion
 *                                detection function.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of sign_motion_en in
 *                      reg EMB_FUNC_EN_A
 *
 */
int32_t lsm6dso_motion_sens_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	reg.emb_func_en_a.sign_motion_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_motion_sens: [get] Enable significant motion
 *                                detection function.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of sign_motion_en in reg EMB_FUNC_EN_A
 *
 */
int32_t lsm6dso_motion_sens_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	*val = reg.emb_func_en_a.sign_motion_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_motion_flag_data_ready: [get] Interrupt status bit
 *                                            for significant motion
 *                                            detection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of is_sigmot in reg EMB_FUNC_STATUS
 *
 */
int32_t lsm6dso_motion_flag_data_ready_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_STATUS, &reg.byte, 1);
	*val = reg.emb_func_status.is_sigmot;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @}
 */

/**
 * @addtogroup  tilt_detection
 * @brief   This section groups all the functions that manage the tilt
 *          event detection.
 * @{
 */

/**
 * @brief  emb_tilt_sens: [set]  Enable tilt calculation.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of tilt_en in reg EMB_FUNC_EN_A
 *
 */
int32_t lsm6dso_tilt_sens_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	reg.emb_func_en_a.tilt_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_tilt_sens: [get]  Enable tilt calculation.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of tilt_en in reg EMB_FUNC_EN_A
 *
 */
int32_t lsm6dso_tilt_sens_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_A, &reg.byte, 1);
	*val = reg.emb_func_en_a.tilt_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   emb_tilt_flag_data_ready: [get] Interrupt status bit for tilt
 *                                    detection
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of is_tilt in reg EMB_FUNC_STATUS
 *
 */
int32_t lsm6dso_tilt_flag_data_ready_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_STATUS, &reg.byte, 1);
	*val = reg.emb_func_status.is_tilt;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @}
 */

/**
 * @addtogroup   magnetometer_sensor
 * @brief   This section groups all the functions that manage additional
 *          magnetometer sensor.
 * @{
 */

/**
 * @brief   mag_sensitivity: [set] External magnetometer sensitivity
 *                                 value register.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_mag_sensitivity_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SENSITIVITY_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SENSITIVITY_H, *buff);

	return mm_error;
}

/**
 * @brief   mag_sensitivity: [get] External magnetometer sensitivity
 *                                 value register.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_mag_sensitivity_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SENSITIVITY_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SENSITIVITY_H, buff);

	return mm_error;
}
/**
 * @brief  mag_offset: [set] Offset for hard-iron compensation
 *                           register (r/w).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_mag_offset_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_OFFX_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_OFFX_H, *buff);
	buff++;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_OFFY_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_OFFY_H, *buff);
	buff++;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_OFFZ_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_OFFZ_H, *buff);

	return mm_error;
}

/**
 * @brief  mag_offset: [get] Offset for hard-iron compensation
 *                           register (r/w).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_mag_offset_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_OFFX_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_OFFX_H, buff);
	buff++;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_OFFY_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_OFFY_H, buff);
	buff++;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_OFFZ_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_OFFZ_H, buff);

	return mm_error;
}
/**
 * @brief  mag_soft_iron: [set] Soft-iron (3x3 symmetric) matrix correction
 *                              register (r/w). The value is expressed as
 *                              half-precision floating-point format:
 *                              SEEEEEFFFFFFFFFF
 *                              S: 1 sign bit;
 *                              E: 5 exponent bits;
 *                              F: 10 fraction bits).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_mag_soft_iron_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_XX_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_XX_H, *buff);
	buff++;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_XY_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_XY_H, *buff);
	buff++;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_XZ_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_XZ_H, *buff);
	buff++;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_YY_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_YY_H, *buff);
	buff++;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_YZ_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_YZ_H, *buff);
	buff++;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_ZZ_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_SI_ZZ_H, *buff);

	return mm_error;
}

/**
 * @brief  mag_soft_iron: [get] Soft-iron (3x3 symmetric) matrix
 *                              correction register (r/w).
 *                              The value is expressed as half-precision
 *                              floating-point format:
 *                              SEEEEEFFFFFFFFFF
 *                              S: 1 sign bit;
 *                              E: 5 exponent bits;
 F: 10 fraction bits.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_mag_soft_iron_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_XX_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_XX_H, buff);
	buff++;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_XY_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_XY_H, buff);
	buff++;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_XZ_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_XZ_H, buff);
	buff++;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_YY_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_YY_H, buff);
	buff++;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_YZ_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_YZ_H, buff);
	buff++;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_ZZ_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_SI_ZZ_H, buff);

	return mm_error;
}

/**
 * @brief   emb_sh_mag_z_orient: [set] Magnetometer Z-axis coordinates
 *                                     rotation (to be aligned to
 *                                     accelerometer/gyroscope axes
 *                                     orientation).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_mag_z_axis_t: change the values of mag_z_axis in
 *                               reg MAG_CFG_A
 *
 */
int32_t lsm6dso_mag_z_orient_set(lsm6dso_ctx_t *ctx, lsm6dso_mag_z_axis_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_CFG_A, &reg.byte);
	reg.mag_cfg_a.mag_z_axis = val;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_CFG_A, reg.byte);

	return mm_error;
}

/**
 * @brief   emb_sh_mag_z_orient: [get] Magnetometer Z-axis coordinates
 *                                     rotation (to be aligned to
 *                                     accelerometer/gyroscope axes
 *                                     orientation).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_mag_z_axis_t: Get the values of mag_z_axis in
 *                               reg MAG_CFG_A
 *
 */
int32_t lsm6dso_mag_z_orient_get(lsm6dso_ctx_t *ctx, lsm6dso_mag_z_axis_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_CFG_A, &reg.byte);
	*val = (lsm6dso_mag_z_axis_t) reg.mag_cfg_a.mag_z_axis;

	return mm_error;
}

/**
 * @brief   emb_sh_mag_y_orient: [set] Magnetometer Y-axis coordinates
 *                                     rotation (to be aligned to
 *                                     accelerometer/gyroscope axes
 *                                     orientation).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_mag_y_axis_t: change the values of mag_y_axis in
 *                               reg MAG_CFG_A
 *
 */
int32_t lsm6dso_mag_y_orient_set(lsm6dso_ctx_t *ctx, lsm6dso_mag_y_axis_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_CFG_A, &reg.byte);
	reg.mag_cfg_a.mag_y_axis = val;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_CFG_A, reg.byte);

	return mm_error;
}

/**
 * @brief   emb_sh_mag_y_orient: [get] Magnetometer Y-axis coordinates
 *                                     rotation (to be aligned to
 *                                     accelerometer/gyroscope axes
 *                                     orientation).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_mag_y_axis_t: Get the values of mag_y_axis in reg MAG_CFG_A
 *
 */
int32_t lsm6dso_mag_y_orient_get(lsm6dso_ctx_t *ctx, lsm6dso_mag_y_axis_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_CFG_A, &reg.byte);
	*val = (lsm6dso_mag_y_axis_t) reg.mag_cfg_a.mag_y_axis;

	return mm_error;
}

/**
 * @brief   emb_sh_mag_x_orient: [set] Magnetometer X-axis coordinates
 *                                     rotation (to be aligned to
 *                                     accelerometer/gyroscope axes
 *                                     orientation).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_mag_x_axis_t: change the values of mag_x_axis in
 *                               reg MAG_CFG_B
 *
 */
int32_t lsm6dso_mag_x_orient_set(lsm6dso_ctx_t *ctx, lsm6dso_mag_x_axis_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_CFG_B, &reg.byte);
	reg.mag_cfg_b.mag_x_axis = val;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_MAG_CFG_B, reg.byte);

	return mm_error;
}

/**
 * @brief   emb_sh_mag_x_orient: [get] Magnetometer X-axis coordinates
 *                                     rotation (to be aligned to
 *                                     accelerometer/gyroscope axes
 *                                     orientation).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_mag_x_axis_t: Get the values of mag_x_axis in
 *                               reg MAG_CFG_B
 *
 */
int32_t lsm6dso_mag_x_orient_get(lsm6dso_ctx_t *ctx, lsm6dso_mag_x_axis_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_MAG_CFG_B, &reg.byte);
	*val = (lsm6dso_mag_x_axis_t) reg.mag_cfg_b.mag_x_axis;

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  significant_motion
 * @brief   This section groups all the functions that manage the
 *          state_machine.
 * @{
 */

/**
 * @brief   emb_long_cnt_flag_data_ready: [get] Interrupt status bit
 *                                              for FSM long counter
 *                                              timeout interrupt event.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of is_fsm_lc in reg EMB_FUNC_STATUS
 *
 */
int32_t lsm6dso_long_cnt_flag_data_ready_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_STATUS, &reg.byte, 1);
	*val = reg.emb_func_status.is_fsm_lc;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_fsm_en: [set]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of fsm_en in reg EMB_FUNC_EN_B
 *
 */
int32_t lsm6dso_emb_fsm_en_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	int32_t mm_error;
	lsm6dso_reg_t reg;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_B, &reg.byte, 1);
	reg.emb_func_en_b.fsm_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_EN_B, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_fsm_en: [get]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t *: return the values of fsm_en in reg EMB_FUNC_EN_B
 *
 */
int32_t lsm6dso_emb_fsm_en_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	int32_t mm_error;
	lsm6dso_reg_t reg;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_B, &reg.byte, 1);
	*val = reg.emb_func_en_b.fsm_en;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_EN_B, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_fsm_enable: [set]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_emb_fsm_enable: union of registers from FSM_ENABLE_A
 *                                 to FSM_ENABLE_B
 *
 */
int32_t lsm6dso_fsm_enable_set(lsm6dso_ctx_t *ctx, lsm6dso_emb_fsm_enable_t *val) {
	int32_t mm_error;
	lsm6dso_reg_t reg;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FSM_ENABLE_A, val->byte, 2);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_EN_B, &reg.byte, 1);

	if (val->byte[0] || val->byte[1]) {
		reg.emb_func_en_b.fsm_en = PROPERTY_ENABLE;
	} else {
		reg.emb_func_en_b.fsm_en = PROPERTY_DISABLE;
	}

	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_EN_B, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_fsm_enable: [get]
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_emb_fsm_enable: union of registers from FSM_ENABLE_A
 *                                 to FSM_ENABLE_B
 *
 */
int32_t lsm6dso_fsm_enable_get(lsm6dso_ctx_t *ctx, lsm6dso_emb_fsm_enable_t *val) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_ENABLE_A, val->byte, 2);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);
	return mm_error;
}

/**
 * @brief  emb_long_cnt: [set] FSM long counter status register.
 *                             Long counter value is an unsigned
 *                             integer value (16-bit format).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_long_cnt_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FSM_LONG_COUNTER_L, buff, 2);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_long_cnt: [get] FSM long counter status register.
 *                             Long counter value is an unsigned
 *                             integer value (16-bit format).
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_long_cnt_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_LONG_COUNTER_L, buff, 2);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @brief  emb_long_clr: [set]  Clear FSM long counter value.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fsm_lc_clr_t: change the values of fsm_lc_clr in
 *                               reg FSM_LONG_COUNTER_CLEAR
 *
 */
int32_t lsm6dso_long_clr_set(lsm6dso_ctx_t *ctx, lsm6dso_fsm_lc_clr_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_LONG_COUNTER_CLEAR, &reg.byte, 1);
	reg.fsm_long_counter_clear.fsm_lc_clr = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_FSM_LONG_COUNTER_CLEAR, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_long_clr: [get]  Clear FSM long counter value.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fsm_lc_clr_t: Get the values of fsm_lc_clr in
 *                               reg  FSM_LONG_COUNTER_CLEAR
 *
 */
int32_t lsm6dso_long_clr_get(lsm6dso_ctx_t *ctx, lsm6dso_fsm_lc_clr_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_LONG_COUNTER_CLEAR, &reg.byte, 1);
	*val = (lsm6dso_fsm_lc_clr_t) reg.fsm_long_counter_clear.fsm_lc_clr;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_fsm_out: [get]  FSM output registers
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fsm_out: union of registers from FSM_OUTS1 to FSM_OUTS16
 *
 */
int32_t lsm6dso_fsm_out_get(lsm6dso_ctx_t *ctx, lsm6dso_fsm_out_t *val) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_FSM_OUTS1, val->byte, 16);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @brief  emb_fsm_data_rate: [set]  Finite State Machine ODR configuration
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fsm_odr_t: change the values of fsm_odr in
 *                            reg EMB_FUNC_ODR_CFG_B
 *
 */
int32_t lsm6dso_fsm_data_rate_set(lsm6dso_ctx_t *ctx, lsm6dso_fsm_odr_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_ODR_CFG_B, &reg.byte, 1);
	reg.emb_func_odr_cfg_b.not_used_01 = 3; /* set default values */
	reg.emb_func_odr_cfg_b.not_used_02 = 1; /* set default values */
	reg.emb_func_odr_cfg_b.fsm_odr = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_ODR_CFG_B, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_fsm_data_rate: [get]  Finite State Machine ODR configuration
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_fsm_odr_t: Get the values of fsm_odr in
 *                            reg EMB_FUNC_ODR_CFG_B
 *
 */
int32_t lsm6dso_fsm_data_rate_get(lsm6dso_ctx_t *ctx, lsm6dso_fsm_odr_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_ODR_CFG_B, &reg.byte, 1);
	*val = (lsm6dso_fsm_odr_t) reg.emb_func_odr_cfg_b.fsm_odr;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_fsm_init: [set]  FSM initialization request.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of fsm_init in reg FSM_INIT
 *
 */
int32_t lsm6dso_fsm_init_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_INIT_B, &reg.byte, 1);
	reg.emb_func_init_b.fsm_init = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_EMB_FUNC_INIT_B, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_fsm_init: [get]  FSM initialization request.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of fsm_init in reg FSM_INIT
 *
 */
int32_t lsm6dso_fsm_init_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_EMBEDDED_FUNC_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_EMB_FUNC_INIT_B, &reg.byte, 1);
	*val = reg.emb_func_init_b.fsm_init;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   long_cnt_int_value: [set] FSM long counter timeout
 *                                    register (r/w). The long counter
 *                                    timeout value is an unsigned integer
 *                                    value (16-bit format).
 *                                    When the long counter value reached
 *                                    this value, the FSM generates
 *                                    an interrupt.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_long_cnt_int_value_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_FSM_LC_TIMEOUT_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_FSM_LC_TIMEOUT_H, *buff);

	return mm_error;
}

/**
 * @brief   long_cnt_int_value: [get] FSM long counter timeout
 *                                    register (r/w). The long counter
 *                                    timeout value is an unsigned integer
 *                                    value (16-bit format).
 *                                    When the long counter value reached
 *                                    this value, the FSM generates
 *                                    an interrupt.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_long_cnt_int_value_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_FSM_LC_TIMEOUT_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_FSM_LC_TIMEOUT_H, buff);

	return mm_error;
}
/**
 * @brief   fsm_number_of_programs: [set]  FSM number of programs register.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_fsm_number_of_programs_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_FSM_PROGRAMS, *buff);
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_FSM_PROGRAMS + 1, *buff);

	return mm_error;
}

/**
 * @brief   fsm_number_of_programs: [get]  FSM number of programs register.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_fsm_number_of_programs_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_FSM_PROGRAMS, buff);

	return mm_error;
}
/**
 * @brief   fsm_start_address: [set] FSM start address register (r/w).
 *                                   First available address is 0x033C.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that contains data to write
 *
 */
int32_t lsm6dso_fsm_start_address_set(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_FSM_START_ADD_L, *buff);
	buff++;
	mm_error = lsm6dso_ln_pg_write_byte(ctx, LSM6DSO_FSM_START_ADD_H, *buff);

	return mm_error;
}

/**
 * @brief   fsm_start_address: [get] FSM start address register (r/w).
 *                                   First available address is 0x033C.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t * : buffer that stores data read
 *
 */
int32_t lsm6dso_fsm_start_address_get(lsm6dso_ctx_t *ctx, uint8_t *buff) {
	int32_t mm_error;

	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_FSM_START_ADD_L, buff);
	buff++;
	mm_error = lsm6dso_ln_pg_read_byte(ctx, LSM6DSO_FSM_START_ADD_H, buff);

	return mm_error;
}

/**
 * @}
 */

/**
 * @addtogroup  Sensor_hub
 * @brief   This section groups all the functions that manage the
 *          sensor hub.
 * @{
 */

/**
 * @brief   sh_read_data_raw: [get]  Sensor hub output registers.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_emb_sh_read_t: union of registers from SENSOR_HUB_1
 *                                to SENSOR_HUB_18
 *
 */
int32_t lsm6dso_sh_read_data_raw_get(lsm6dso_ctx_t *ctx, lsm6dso_emb_sh_read_t *val) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SENSOR_HUB_1, (uint8_t*) val, 18);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}
/**
 * @brief   sh_slave_connected: [set] Number of external sensors to be read
 *                                    by the sensor hub.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_aux_sens_on_t: change the values of aux_sens_on in
 *                                reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_slave_connected_set(lsm6dso_ctx_t *ctx, lsm6dso_aux_sens_on_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	reg.master_config.aux_sens_on = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   sh_slave_connected: [get] Number of external sensors to be
 *                                    read by the sensor hub.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_aux_sens_on_t: Get the values of aux_sens_on in
 *                                reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_slave_connected_get(lsm6dso_ctx_t *ctx, lsm6dso_aux_sens_on_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	*val = (lsm6dso_aux_sens_on_t) reg.master_config.aux_sens_on;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_master: [set]  Sensor hub I2C master enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of master_on in reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_master_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	reg.master_config.master_on = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_master: [get]  Sensor hub I2C master enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of master_on in reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_master_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	*val = reg.master_config.master_on;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_pin_mode: [set]  Master I2C pull-up enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_shub_pu_en_t: change the values of shub_pu_en in
 *                               reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_pin_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_shub_pu_en_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	reg.master_config.shub_pu_en = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_pin_mode: [get]  Master I2C pull-up enable.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_shub_pu_en_t: Get the values of shub_pu_en in
 *                               reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_pin_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_shub_pu_en_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	*val = (lsm6dso_shub_pu_en_t) reg.master_config.shub_pu_en;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   sh_pass_through: [set]  I2C interface pass-through.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t val: change the values of pass_through_mode in
 *                      reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_pass_through_set(lsm6dso_ctx_t *ctx, uint8_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	reg.master_config.pass_through_mode = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief   sh_pass_through: [get]  I2C interface pass-through.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of pass_through_mode in
 *                  reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_pass_through_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	*val = reg.master_config.pass_through_mode;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_syncro_mode: [set]  Sensor hub trigger signal selection.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_start_config_t: change the values of start_config in
 *                                 reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_syncro_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_start_config_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	reg.master_config.start_config = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_syncro_mode: [get]  Sensor hub trigger signal selection.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_start_config_t: Get the values of start_config in
 *                                 reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_syncro_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_start_config_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	*val = (lsm6dso_start_config_t) reg.master_config.start_config;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_write_mode: [set] Slave 0 write operation is performed
 *                              only at the first sensor hub cycle.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_write_once_t: change the values of write_once in
 *                               reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_write_mode_set(lsm6dso_ctx_t *ctx, lsm6dso_write_once_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	reg.master_config.write_once = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_write_mode: [get] Slave 0 write operation is performed
 *                              only at the first sensor hub cycle.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_write_once_t: Get the values of write_once in
 *                               reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_write_mode_get(lsm6dso_ctx_t *ctx, lsm6dso_write_once_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	*val = (lsm6dso_write_once_t) reg.master_config.write_once;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_reset: [set]  Reset Master logic and output registers.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 *
 */
int32_t lsm6dso_sh_reset_set(lsm6dso_ctx_t *ctx) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	reg.master_config.rst_master_regs = PROPERTY_ENABLE;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	reg.master_config.rst_master_regs = PROPERTY_DISABLE;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_reset: [get]  Reset Master logic and output registers.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  uint8_t: change the values of rst_master_regs in reg MASTER_CONFIG
 *
 */
int32_t lsm6dso_sh_reset_get(lsm6dso_ctx_t *ctx, uint8_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_MASTER_CONFIG, &reg.byte, 1);
	*val = reg.master_config.rst_master_regs;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  emb_sh_data_rate: [set]  Rate at which the master communicates.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_shub_odr_t: change the values of shub_odr in
 *                             reg slv1_CONFIG
 *
 */
int32_t lsm6dso_sh_data_rate_set(lsm6dso_ctx_t *ctx, lsm6dso_shub_odr_t val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV1_CONFIG, &reg.byte, 1);
	reg.slv0_config.shub_odr = val;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV1_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_data_rate: [get]  Rate at which the master communicates.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_shub_odr_t: Get the values of shub_odr in reg slv1_CONFIG
 *
 */
int32_t lsm6dso_sh_data_rate_get(lsm6dso_ctx_t *ctx, lsm6dso_shub_odr_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV1_CONFIG, &reg.byte, 1);
	*val = (lsm6dso_shub_odr_t) reg.slv0_config.shub_odr;
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_cfg_write: Configure slave 0 for perform a write.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sh_cfg_write_t: a structure that contain
 *                      - uint8_t slv1_add;    8 bit i2c device address
 *                      - uint8_t slv1_subadd; 8 bit register device address
 *                      - uint8_t slv1_data;   8 bit data to write
 *
 */
int32_t lsm6dso_sh_cfg_write(lsm6dso_ctx_t *ctx, lsm6dso_sh_cfg_write_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	reg.byte = val->slv0_add;
	reg.slv0_add.rw_0 = 0;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV0_ADD, &reg.byte, 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV0_SUBADD, &(val->slv0_subadd), 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_DATAWRITE_SRC_MODE_SUB_SLV0, &(val->slv0_data), 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_slv0_cfg_read: [get] Configure slave 0 for perform a write/read.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sh_cfg_read_t: a structure that contain
 *                      - uint8_t slv1_add;    8 bit i2c device address
 *                      - uint8_t slv1_subadd; 8 bit register device address
 *                      - uint8_t slv1_len;    num of bit to read
 *
 */
int32_t lsm6dso_sh_slv0_cfg_read(lsm6dso_ctx_t *ctx, lsm6dso_sh_cfg_read_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	reg.byte = val->slv_add;
	reg.slv0_add.rw_0 = 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV0_ADD, &reg.byte, 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV0_SUBADD, &(val->slv_subadd), 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV0_CONFIG, &reg.byte, 1);
	reg.slv0_config.slave0_numop = val->slv_len;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV0_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_slv1_cfg_read: [get] Configure slave 0 for perform a write/read.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sh_cfg_read_t: a structure that contain
 *                      - uint8_t slv1_add;    8 bit i2c device address
 *                      - uint8_t slv1_subadd; 8 bit register device address
 *                      - uint8_t slv1_len;    num of bit to read
 *
 */
int32_t lsm6dso_sh_slv1_cfg_read(lsm6dso_ctx_t *ctx, lsm6dso_sh_cfg_read_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	reg.byte = val->slv_add;
	reg.slv1_add.r_1 = 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV1_ADD, &reg.byte, 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV1_SUBADD, &(val->slv_subadd), 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV1_CONFIG, &reg.byte, 1);
	reg.slv1_config.slave1_numop = val->slv_len;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV1_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_slv2_cfg_read: [get] Configure slave 0 for perform a write/read.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sh_cfg_read_t: a structure that contain
 *                      - uint8_t slv2_add;    8 bit i2c device address
 *                      - uint8_t slv2_subadd; 8 bit register device address
 *                      - uint8_t slv2_len;    num of bit to read
 *
 */
int32_t lsm6dso_sh_slv2_cfg_read(lsm6dso_ctx_t *ctx, lsm6dso_sh_cfg_read_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	reg.byte = val->slv_add;
	reg.slv2_add.r_2 = 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV2_ADD, &reg.byte, 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV2_SUBADD, &(val->slv_subadd), 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV2_CONFIG, &reg.byte, 1);
	reg.slv2_config.slave2_numop = val->slv_len;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV2_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_slv3_cfg_read: [get] Configure slave 0 for perform a write/read.
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_sh_cfg_read_t: a structure that contain
 *                      - uint8_t slv3_add;    8 bit i2c device address
 *                      - uint8_t slv3_subadd; 8 bit register device address
 *                      - uint8_t slv3_len;    num of bit to read
 *
 */
int32_t lsm6dso_sh_slv3_cfg_read(lsm6dso_ctx_t *ctx, lsm6dso_sh_cfg_read_t *val) {
	lsm6dso_reg_t reg;
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	reg.byte = val->slv_add;
	reg.slv3_add.r_3 = 1;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV3_ADD, &reg.byte, 1);
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV3_SUBADD, &(val->slv_subadd), 1);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_SLV3_CONFIG, &reg.byte, 1);
	reg.slv3_config.slave3_numop = val->slv_len;
	mm_error = lsm6dso_write_reg(ctx, LSM6DSO_SLV3_CONFIG, &reg.byte, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @brief  sh_status: [get]  Sensor hub source register
 *
 * @param  lsm6dso_ctx_t *ctx: read / write interface definitions
 * @param  lsm6dso_status_master: union of registers from STATUS_MASTER to
 *
 */
int32_t lsm6dso_sh_status_get(lsm6dso_ctx_t *ctx, lsm6dso_status_master_t *val) {
	int32_t mm_error;

	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_SENSOR_HUB_BANK);
	mm_error = lsm6dso_read_reg(ctx, LSM6DSO_STATUS_MASTER, (uint8_t*) val, 1);
	mm_error = lsm6dso_mem_bank_set(ctx, LSM6DSO_USER_BANK);

	return mm_error;
}

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
