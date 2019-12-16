#include "eapp_utils.h"
#include "eapp_func.h"
#include "edge_call.h"
#include <syscall.h>
#include "malloc.h"
#include "string.h"
#include "edge_call.h"
#include "h2ecall.h"
#include "common_header.h"
#include "ocalls.h"
#include "ocalls_common.h"
#include "ocalls_builder.h"
#include "ocalls_reader.h"

int __wrapper_calc_message(void* input, void** output) {
	encl_message_t msg;
	__ocall_wrapper_calc_message_table_t function_reference = __ocall_wrapper_calc_message_as_root(input);
	encl_message_t_table_t __flatcc_reference_msg = __ocall_wrapper_calc_message_msg(function_reference);
	{
		{
			msg.len = encl_message_t_len(__flatcc_reference_msg);
		}
		{
			msg.host_ptr = (void *) malloc((1 * (msg.len)) * sizeof(char));
			for (size_t i3_0 = 0; i3_0 < (size_t) (msg.len); ++i3_0) {
				{
					((char*) msg.host_ptr)[i3_0] = flatbuffers_int8_vec_at(encl_message_t_host_ptr(__flatcc_reference_msg), i3_0 + (msg.len) * (0));
				}
			}
		}
		
	}
	encl_message_t ret_val;
	ret_val = calc_message(msg);
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_calc_message_start_as_root(&builder);
	encl_message_t_ref_t __flatcc_reference_ret_val;
	{
		encl_message_t_start(&builder);
		unsigned long __2_len;
		{
			__2_len = ret_val.len;
		}
		flatbuffers_int8_vec_ref_t __2_host_ptr;
		{
			char* __keyedge_array_data_3 = (char*) malloc(1 * (ret_val.len) * sizeof(char));
			for (size_t i3_0 = 0; i3_0 < (size_t) (ret_val.len); ++i3_0) {
				{
					__keyedge_array_data_3[i3_0 + (ret_val.len) * (0)] = ((char*) ret_val.host_ptr)[i3_0];
				}
			}
			__2_host_ptr = flatbuffers_int8_vec_create(&builder, (signed char*) __keyedge_array_data_3, 1 * (ret_val.len));
			free(__keyedge_array_data_3);
		}
		encl_message_t_host_ptr_add(&builder, __2_host_ptr);
		encl_message_t_len_add(&builder, __2_len);
		__flatcc_reference_ret_val = encl_message_t_end(&builder);
	}
	__ocall_wrapper_calc_message___return_value_add(&builder, __flatcc_reference_ret_val);
	__ocall_wrapper_calc_message_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	*output = __buf;
	return (int) __size;
}
int __wrapper_get_attestation_report(void* input, void** output) {
	__ocall_wrapper_get_attestation_report_table_t function_reference = __ocall_wrapper_get_attestation_report_as_root(input);
	report ret_val;
	ret_val = get_attestation_report();
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_get_attestation_report_start_as_root(&builder);
	report_ref_t __flatcc_reference_ret_val;
	{
		report_start(&builder);
		flatbuffers_int8_vec_ref_t __2_data;
		{
			char* __keyedge_array_data_3 = (char*) malloc(1 * (2048) * sizeof(char));
			for (size_t i3_0 = 0; i3_0 < (size_t) (2048); ++i3_0) {
				{
					__keyedge_array_data_3[i3_0 + (2048) * (0)] = ( ret_val.data)[i3_0];
				}
			}
			__2_data = flatbuffers_int8_vec_create(&builder, (signed char*) __keyedge_array_data_3, 1 * (2048));
			free(__keyedge_array_data_3);
		}
		report_data_add(&builder, __2_data);
		__flatcc_reference_ret_val = report_end(&builder);
	}
	__ocall_wrapper_get_attestation_report___return_value_add(&builder, __flatcc_reference_ret_val);
	__ocall_wrapper_get_attestation_report_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	*output = __buf;
	return (int) __size;
}
unsigned long print_buffer(char *str) {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	size_t __0_str_keyedge_size = strlen(str) + 1;
	flatbuffers_int8_vec_ref_t __0_str;
	{
		char* __keyedge_array_data_2 = (char*) malloc(1 * (__0_str_keyedge_size) * sizeof(char));
		for (size_t i2_0 = 0; i2_0 < (size_t) (__0_str_keyedge_size); ++i2_0) {
			{
				__keyedge_array_data_2[i2_0 + (__0_str_keyedge_size) * (0)] = ( str)[i2_0];
			}
		}
		__0_str = flatbuffers_int8_vec_create(&builder, (signed char*) __keyedge_array_data_2, 1 * (__0_str_keyedge_size));
		free(__keyedge_array_data_2);
	}
	__ocall_wrapper_print_buffer_start_as_root(&builder);
	__ocall_wrapper_print_buffer_str_add(&builder, __0_str);
	__ocall_wrapper_print_buffer_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	char return_address[1024];
	ocall(__function_print_buffer, __buf, __size, return_address, 1024);
	free(__buf);
	flatcc_builder_clear(&builder);
	unsigned long __return_value;
	{
		__return_value = __ocall_wrapper_print_buffer___return_value(__ocall_wrapper_print_buffer_as_root(return_address));
	};
	return __return_value;
}
void print_value(unsigned long val) {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	unsigned long __0_val;
	{
		__0_val = val;
	}
	__ocall_wrapper_print_value_start_as_root(&builder);
	__ocall_wrapper_print_value_val_add(&builder, __0_val);
	__ocall_wrapper_print_value_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	char return_address[1024];
	ocall(__function_print_value, __buf, __size, return_address, 1024);
	free(__buf);
	flatcc_builder_clear(&builder);
}
int __wrapper_set_client_pk(void* input, void** output) {
	pubkey *pk;
	__ocall_wrapper_set_client_pk_table_t function_reference = __ocall_wrapper_set_client_pk_as_root(input);
	__pointer_pubkey_table_t __flatcc_reference_pk = __ocall_wrapper_set_client_pk_pk(function_reference);
	{
		if (__pointer_pubkey___is_null(__flatcc_reference_pk)) {
			pk = 0;
		} else {
			pk = (pubkey *) malloc(sizeof(pubkey));
			{
				{
					
					for (size_t i5_0 = 0; i5_0 < (size_t) (32); ++i5_0) {
						{
							( (*pk).data)[i5_0] = flatbuffers_int8_vec_at(pubkey_data(__pointer_pubkey___data(__flatcc_reference_pk)), i5_0 + (32) * (0));
						}
					}
				}
				
			}
		}
	}
	int ret_val;
	ret_val = set_client_pk(pk);
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_set_client_pk_start_as_root(&builder);
	int __flatcc_reference_ret_val;
	{
		__flatcc_reference_ret_val = ret_val;
	}
	__ocall_wrapper_set_client_pk___return_value_add(&builder, __flatcc_reference_ret_val);
	__ocall_wrapper_set_client_pk_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	*output = __buf;
	return (int) __size;
}
void register_inverse_functions() {
	h2ecall_list[__function_calc_message] = __wrapper_calc_message;
	h2ecall_list[__function_get_attestation_report] = __wrapper_get_attestation_report;
	h2ecall_list[__function_set_client_pk] = __wrapper_set_client_pk;
	return;
}
