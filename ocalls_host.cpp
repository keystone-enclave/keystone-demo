#include <keystone.h>
#include <edge_call.h>
#include "ocalls.h"
#include "ocalls_common.h"
#include "ocalls_builder.h"
#include "ocalls_reader.h"
extern Keystone enclave;

encl_message_t calc_message(encl_message_t msg) {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	encl_message_t_ref_t __0_msg;
	{
		encl_message_t_start(&builder);
		unsigned long __2_len;
		{
			__2_len = msg.len;
		}
		flatbuffers_int8_vec_ref_t __2_host_ptr;
		{
			char* __keyedge_array_data_3 = (char*) malloc(1 * (msg.len) * sizeof(char));
			for (size_t i3_0 = 0; i3_0 < (size_t) (msg.len); ++i3_0) {
				{
					__keyedge_array_data_3[i3_0 + (msg.len) * (0)] = ((char*) msg.host_ptr)[i3_0];
				}
			}
			__2_host_ptr = flatbuffers_int8_vec_create(&builder, (signed char*) __keyedge_array_data_3, 1 * (msg.len));
			free(__keyedge_array_data_3);
		}
		encl_message_t_host_ptr_add(&builder, __2_host_ptr);
		encl_message_t_len_add(&builder, __2_len);
		__0_msg = encl_message_t_end(&builder);
	}
	__ocall_wrapper_calc_message_start_as_root(&builder);
	__ocall_wrapper_calc_message_msg_add(&builder, __0_msg);
	__ocall_wrapper_calc_message_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	*(int*) _shared_start = sizeof(int) + __size;
	*(((int*) _shared_start) + 1) = __function_calc_message;
	memcpy((char*) _shared_start + 2 * sizeof(int), (char*) __buf, __size);
	enclave.resume();
	free(__buf);
	flatcc_builder_clear(&builder);
	edge_call* __result = (edge_call*) _shared_start;
	encl_message_t __return_value;
	{
		{
			__return_value.len = encl_message_t_len(__ocall_wrapper_calc_message___return_value(__ocall_wrapper_calc_message_as_root((char*) _shared_start + __result -> call_arg_offset)));
		}
		{
			__return_value.host_ptr = (void *) malloc((1 * (__return_value.len)) * sizeof(char));
			for (size_t i3_0 = 0; i3_0 < (size_t) (__return_value.len); ++i3_0) {
				{
					((char*) __return_value.host_ptr)[i3_0] = flatbuffers_int8_vec_at(encl_message_t_host_ptr(__ocall_wrapper_calc_message___return_value(__ocall_wrapper_calc_message_as_root((char*) _shared_start + __result -> call_arg_offset))), i3_0 + (__return_value.len) * (0));
				}
			}
		}
		
	};
	return __return_value;
}
void __wrapper_end_enclave(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	__ocall_wrapper_end_enclave_table_t function_reference = __ocall_wrapper_end_enclave_as_root((void *) call_args);
	end_enclave();
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_end_enclave_start_as_root(&builder);
	__ocall_wrapper_end_enclave_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
report get_attestation_report() {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_get_attestation_report_start_as_root(&builder);
	__ocall_wrapper_get_attestation_report_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	*(int*) _shared_start = sizeof(int) + __size;
	*(((int*) _shared_start) + 1) = __function_get_attestation_report;
	memcpy((char*) _shared_start + 2 * sizeof(int), (char*) __buf, __size);
	enclave.resume();
	free(__buf);
	flatcc_builder_clear(&builder);
	edge_call* __result = (edge_call*) _shared_start;
	report __return_value;
	{
		{
			
			for (size_t i3_0 = 0; i3_0 < (size_t) (2048); ++i3_0) {
				{
					( __return_value.data)[i3_0] = flatbuffers_int8_vec_at(report_data(__ocall_wrapper_get_attestation_report___return_value(__ocall_wrapper_get_attestation_report_as_root((char*) _shared_start + __result -> call_arg_offset))), i3_0 + (2048) * (0));
				}
			}
		}
		
	};
	return __return_value;
}
void __wrapper_print_buffer(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	char *str;
	__ocall_wrapper_print_buffer_table_t function_reference = __ocall_wrapper_print_buffer_as_root((void *) call_args);
size_t __0_str_keyedge_size = flatbuffers_int8_vec_len(__ocall_wrapper_print_buffer_str(function_reference));
	flatbuffers_int8_vec_t __flatcc_reference_str = __ocall_wrapper_print_buffer_str(function_reference);
	{
		str = (char *) malloc((1 * (__0_str_keyedge_size)) * sizeof(char));
		for (size_t i2_0 = 0; i2_0 < (size_t) (__0_str_keyedge_size); ++i2_0) {
			{
				( str)[i2_0] = flatbuffers_int8_vec_at(__flatcc_reference_str, i2_0 + (__0_str_keyedge_size) * (0));
			}
		}
	}
	unsigned long ret_val;
	ret_val = print_buffer(str);
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_print_buffer_start_as_root(&builder);
	unsigned long __flatcc_reference_ret_val;
	{
		__flatcc_reference_ret_val = ret_val;
	}
	__ocall_wrapper_print_buffer___return_value_add(&builder, __flatcc_reference_ret_val);
	__ocall_wrapper_print_buffer_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
void __wrapper_print_value(void* buffer) {
	struct edge_call* edge_call = (struct edge_call*) buffer;
	uintptr_t call_args;
	size_t arg_len;
	if (edge_call_args_ptr(edge_call, &call_args, &arg_len) != 0) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_OFFSET;
		return;
	}
	unsigned long val;
	__ocall_wrapper_print_value_table_t function_reference = __ocall_wrapper_print_value_as_root((void *) call_args);
	unsigned long __flatcc_reference_val = __ocall_wrapper_print_value_val(function_reference);
	{
		val = __flatcc_reference_val;
	}
	print_value(val);
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__ocall_wrapper_print_value_start_as_root(&builder);
	__ocall_wrapper_print_value_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	uintptr_t data_section = edge_call_data_ptr();
	memcpy((void *) data_section, __buf, __size);
	free(__buf);
	flatcc_builder_clear(&builder);
	if (edge_call_setup_ret(edge_call, (void*) data_section, 1024)) {
		edge_call -> return_data.call_status = CALL_STATUS_BAD_PTR;
	} else {
		edge_call -> return_data.call_status = CALL_STATUS_OK;
	}
	return;
}
int set_client_pk(pubkey *pk) {
	flatcc_builder_t builder;
	flatcc_builder_init(&builder);
	__pointer_pubkey_ref_t __0_pk;
	{
		if (pk) {
			pubkey_ref_t __keyedge_pointer_data_2;
			{
				pubkey_start(&builder);
				flatbuffers_int8_vec_ref_t __4_data;
				{
					char* __keyedge_array_data_5 = (char*) malloc(1 * (32) * sizeof(char));
					for (size_t i5_0 = 0; i5_0 < (size_t) (32); ++i5_0) {
						{
							__keyedge_array_data_5[i5_0 + (32) * (0)] = ( (*pk).data)[i5_0];
						}
					}
					__4_data = flatbuffers_int8_vec_create(&builder, (signed char*) __keyedge_array_data_5, 1 * (32));
					free(__keyedge_array_data_5);
				}
				pubkey_data_add(&builder, __4_data);
				__keyedge_pointer_data_2 = pubkey_end(&builder);
			}
			__0_pk = __pointer_pubkey_create(&builder, 0, __keyedge_pointer_data_2);
		} else {
			__pointer_pubkey_start(&builder);
			__pointer_pubkey___is_null_add(&builder, 1);
			__0_pk = __pointer_pubkey_end(&builder);
		}
	}
	__ocall_wrapper_set_client_pk_start_as_root(&builder);
	__ocall_wrapper_set_client_pk_pk_add(&builder, __0_pk);
	__ocall_wrapper_set_client_pk_end_as_root(&builder);
	void* __buf;
	size_t __size;
	__buf = (void *) flatcc_builder_finalize_buffer(&builder, &__size);
	*(int*) _shared_start = sizeof(int) + __size;
	*(((int*) _shared_start) + 1) = __function_set_client_pk;
	memcpy((char*) _shared_start + 2 * sizeof(int), (char*) __buf, __size);
	enclave.resume();
	free(__buf);
	flatcc_builder_clear(&builder);
	edge_call* __result = (edge_call*) _shared_start;
	int __return_value;
	{
		__return_value = __ocall_wrapper_set_client_pk___return_value(__ocall_wrapper_set_client_pk_as_root((char*) _shared_start + __result -> call_arg_offset));
	};
	return __return_value;
}
void register_functions() {
	register_call(__function_end_enclave, __wrapper_end_enclave);
	register_call(__function_print_buffer, __wrapper_print_buffer);
	register_call(__function_print_value, __wrapper_print_value);
	return;
}