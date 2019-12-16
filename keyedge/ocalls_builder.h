#ifndef OCALLS_BUILDER_H
#define OCALLS_BUILDER_H

/* Generated by flatcc 0.6.1-dev FlatBuffers schema compiler for C by dvide.com */

#ifndef OCALLS_READER_H
#include "ocalls_reader.h"
#endif
#ifndef FLATBUFFERS_COMMON_BUILDER_H
#include "flatbuffers_common_builder.h"
#endif
#include "flatcc/flatcc_prologue.h"
#ifndef flatbuffers_identifier
#define flatbuffers_identifier 0
#endif
#ifndef flatbuffers_extension
#define flatbuffers_extension ".bin"
#endif

static const flatbuffers_voffset_t __report_required[] = { 0 };
typedef flatbuffers_ref_t report_ref_t;
static report_ref_t report_clone(flatbuffers_builder_t *B, report_table_t t);
__flatbuffers_build_table(flatbuffers_, report, 1)

static const flatbuffers_voffset_t __pubkey_required[] = { 0 };
typedef flatbuffers_ref_t pubkey_ref_t;
static pubkey_ref_t pubkey_clone(flatbuffers_builder_t *B, pubkey_table_t t);
__flatbuffers_build_table(flatbuffers_, pubkey, 1)

static const flatbuffers_voffset_t __encl_message_t_required[] = { 0 };
typedef flatbuffers_ref_t encl_message_t_ref_t;
static encl_message_t_ref_t encl_message_t_clone(flatbuffers_builder_t *B, encl_message_t_table_t t);
__flatbuffers_build_table(flatbuffers_, encl_message_t, 2)

static const flatbuffers_voffset_t ____pointer_flatbuffers_int8_required[] = { 0 };
typedef flatbuffers_ref_t __pointer_flatbuffers_int8_ref_t;
static __pointer_flatbuffers_int8_ref_t __pointer_flatbuffers_int8_clone(flatbuffers_builder_t *B, __pointer_flatbuffers_int8_table_t t);
__flatbuffers_build_table(flatbuffers_, __pointer_flatbuffers_int8, 2)

static const flatbuffers_voffset_t ____pointer_pubkey_required[] = { 0 };
typedef flatbuffers_ref_t __pointer_pubkey_ref_t;
static __pointer_pubkey_ref_t __pointer_pubkey_clone(flatbuffers_builder_t *B, __pointer_pubkey_table_t t);
__flatbuffers_build_table(flatbuffers_, __pointer_pubkey, 2)

static const flatbuffers_voffset_t ____ocall_wrapper_calc_message_required[] = { 0 };
typedef flatbuffers_ref_t __ocall_wrapper_calc_message_ref_t;
static __ocall_wrapper_calc_message_ref_t __ocall_wrapper_calc_message_clone(flatbuffers_builder_t *B, __ocall_wrapper_calc_message_table_t t);
__flatbuffers_build_table(flatbuffers_, __ocall_wrapper_calc_message, 2)

static const flatbuffers_voffset_t ____ocall_wrapper_get_attestation_report_required[] = { 0 };
typedef flatbuffers_ref_t __ocall_wrapper_get_attestation_report_ref_t;
static __ocall_wrapper_get_attestation_report_ref_t __ocall_wrapper_get_attestation_report_clone(flatbuffers_builder_t *B, __ocall_wrapper_get_attestation_report_table_t t);
__flatbuffers_build_table(flatbuffers_, __ocall_wrapper_get_attestation_report, 1)

static const flatbuffers_voffset_t ____ocall_wrapper_print_buffer_required[] = { 0 };
typedef flatbuffers_ref_t __ocall_wrapper_print_buffer_ref_t;
static __ocall_wrapper_print_buffer_ref_t __ocall_wrapper_print_buffer_clone(flatbuffers_builder_t *B, __ocall_wrapper_print_buffer_table_t t);
__flatbuffers_build_table(flatbuffers_, __ocall_wrapper_print_buffer, 2)

static const flatbuffers_voffset_t ____ocall_wrapper_print_value_required[] = { 0 };
typedef flatbuffers_ref_t __ocall_wrapper_print_value_ref_t;
static __ocall_wrapper_print_value_ref_t __ocall_wrapper_print_value_clone(flatbuffers_builder_t *B, __ocall_wrapper_print_value_table_t t);
__flatbuffers_build_table(flatbuffers_, __ocall_wrapper_print_value, 2)

static const flatbuffers_voffset_t ____ocall_wrapper_set_client_pk_required[] = { 0 };
typedef flatbuffers_ref_t __ocall_wrapper_set_client_pk_ref_t;
static __ocall_wrapper_set_client_pk_ref_t __ocall_wrapper_set_client_pk_clone(flatbuffers_builder_t *B, __ocall_wrapper_set_client_pk_table_t t);
__flatbuffers_build_table(flatbuffers_, __ocall_wrapper_set_client_pk, 2)

#define __report_formal_args , flatbuffers_int8_vec_ref_t v0
#define __report_call_args , v0
static inline report_ref_t report_create(flatbuffers_builder_t *B __report_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, report, report_identifier, report_type_identifier)

#define __pubkey_formal_args , flatbuffers_int8_vec_ref_t v0
#define __pubkey_call_args , v0
static inline pubkey_ref_t pubkey_create(flatbuffers_builder_t *B __pubkey_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, pubkey, pubkey_identifier, pubkey_type_identifier)

#define __encl_message_t_formal_args , flatbuffers_int8_vec_ref_t v0, uint32_t v1
#define __encl_message_t_call_args , v0, v1
static inline encl_message_t_ref_t encl_message_t_create(flatbuffers_builder_t *B __encl_message_t_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, encl_message_t, encl_message_t_identifier, encl_message_t_type_identifier)

#define ____pointer_flatbuffers_int8_formal_args , flatbuffers_bool_t v0, int8_t v1
#define ____pointer_flatbuffers_int8_call_args , v0, v1
static inline __pointer_flatbuffers_int8_ref_t __pointer_flatbuffers_int8_create(flatbuffers_builder_t *B ____pointer_flatbuffers_int8_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, __pointer_flatbuffers_int8, __pointer_flatbuffers_int8_identifier, __pointer_flatbuffers_int8_type_identifier)

#define ____pointer_pubkey_formal_args , flatbuffers_bool_t v0, pubkey_ref_t v1
#define ____pointer_pubkey_call_args , v0, v1
static inline __pointer_pubkey_ref_t __pointer_pubkey_create(flatbuffers_builder_t *B ____pointer_pubkey_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, __pointer_pubkey, __pointer_pubkey_identifier, __pointer_pubkey_type_identifier)

#define ____ocall_wrapper_calc_message_formal_args , encl_message_t_ref_t v0, encl_message_t_ref_t v1
#define ____ocall_wrapper_calc_message_call_args , v0, v1
static inline __ocall_wrapper_calc_message_ref_t __ocall_wrapper_calc_message_create(flatbuffers_builder_t *B ____ocall_wrapper_calc_message_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, __ocall_wrapper_calc_message, __ocall_wrapper_calc_message_identifier, __ocall_wrapper_calc_message_type_identifier)

#define ____ocall_wrapper_get_attestation_report_formal_args , report_ref_t v0
#define ____ocall_wrapper_get_attestation_report_call_args , v0
static inline __ocall_wrapper_get_attestation_report_ref_t __ocall_wrapper_get_attestation_report_create(flatbuffers_builder_t *B ____ocall_wrapper_get_attestation_report_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, __ocall_wrapper_get_attestation_report, __ocall_wrapper_get_attestation_report_identifier, __ocall_wrapper_get_attestation_report_type_identifier)

#define ____ocall_wrapper_print_buffer_formal_args , flatbuffers_int8_vec_ref_t v0, uint32_t v1
#define ____ocall_wrapper_print_buffer_call_args , v0, v1
static inline __ocall_wrapper_print_buffer_ref_t __ocall_wrapper_print_buffer_create(flatbuffers_builder_t *B ____ocall_wrapper_print_buffer_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, __ocall_wrapper_print_buffer, __ocall_wrapper_print_buffer_identifier, __ocall_wrapper_print_buffer_type_identifier)

#define ____ocall_wrapper_print_value_formal_args , uint32_t v0, int8_t v1
#define ____ocall_wrapper_print_value_call_args , v0, v1
static inline __ocall_wrapper_print_value_ref_t __ocall_wrapper_print_value_create(flatbuffers_builder_t *B ____ocall_wrapper_print_value_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, __ocall_wrapper_print_value, __ocall_wrapper_print_value_identifier, __ocall_wrapper_print_value_type_identifier)

#define ____ocall_wrapper_set_client_pk_formal_args , __pointer_pubkey_ref_t v0, int32_t v1
#define ____ocall_wrapper_set_client_pk_call_args , v0, v1
static inline __ocall_wrapper_set_client_pk_ref_t __ocall_wrapper_set_client_pk_create(flatbuffers_builder_t *B ____ocall_wrapper_set_client_pk_formal_args);
__flatbuffers_build_table_prolog(flatbuffers_, __ocall_wrapper_set_client_pk, __ocall_wrapper_set_client_pk_identifier, __ocall_wrapper_set_client_pk_type_identifier)

__flatbuffers_build_vector_field(0, flatbuffers_, report_data, flatbuffers_int8, int8_t, report)

static inline report_ref_t report_create(flatbuffers_builder_t *B __report_formal_args)
{
    if (report_start(B)
        || report_data_add(B, v0)) {
        return 0;
    }
    return report_end(B);
}

static report_ref_t report_clone(flatbuffers_builder_t *B, report_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (report_start(B)
        || report_data_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, report_end(B));
}

__flatbuffers_build_vector_field(0, flatbuffers_, pubkey_data, flatbuffers_int8, int8_t, pubkey)

static inline pubkey_ref_t pubkey_create(flatbuffers_builder_t *B __pubkey_formal_args)
{
    if (pubkey_start(B)
        || pubkey_data_add(B, v0)) {
        return 0;
    }
    return pubkey_end(B);
}

static pubkey_ref_t pubkey_clone(flatbuffers_builder_t *B, pubkey_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (pubkey_start(B)
        || pubkey_data_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, pubkey_end(B));
}

__flatbuffers_build_vector_field(0, flatbuffers_, encl_message_t_host_ptr, flatbuffers_int8, int8_t, encl_message_t)
__flatbuffers_build_scalar_field(1, flatbuffers_, encl_message_t_len, flatbuffers_uint32, uint32_t, 4, 4, UINT32_C(0), encl_message_t)

static inline encl_message_t_ref_t encl_message_t_create(flatbuffers_builder_t *B __encl_message_t_formal_args)
{
    if (encl_message_t_start(B)
        || encl_message_t_host_ptr_add(B, v0)
        || encl_message_t_len_add(B, v1)) {
        return 0;
    }
    return encl_message_t_end(B);
}

static encl_message_t_ref_t encl_message_t_clone(flatbuffers_builder_t *B, encl_message_t_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (encl_message_t_start(B)
        || encl_message_t_host_ptr_pick(B, t)
        || encl_message_t_len_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, encl_message_t_end(B));
}

__flatbuffers_build_scalar_field(0, flatbuffers_, __pointer_flatbuffers_int8___is_null, flatbuffers_bool, flatbuffers_bool_t, 1, 1, UINT8_C(0), __pointer_flatbuffers_int8)
__flatbuffers_build_scalar_field(1, flatbuffers_, __pointer_flatbuffers_int8___data, flatbuffers_int8, int8_t, 1, 1, INT8_C(0), __pointer_flatbuffers_int8)

static inline __pointer_flatbuffers_int8_ref_t __pointer_flatbuffers_int8_create(flatbuffers_builder_t *B ____pointer_flatbuffers_int8_formal_args)
{
    if (__pointer_flatbuffers_int8_start(B)
        || __pointer_flatbuffers_int8___is_null_add(B, v0)
        || __pointer_flatbuffers_int8___data_add(B, v1)) {
        return 0;
    }
    return __pointer_flatbuffers_int8_end(B);
}

static __pointer_flatbuffers_int8_ref_t __pointer_flatbuffers_int8_clone(flatbuffers_builder_t *B, __pointer_flatbuffers_int8_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (__pointer_flatbuffers_int8_start(B)
        || __pointer_flatbuffers_int8___is_null_pick(B, t)
        || __pointer_flatbuffers_int8___data_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, __pointer_flatbuffers_int8_end(B));
}

__flatbuffers_build_scalar_field(0, flatbuffers_, __pointer_pubkey___is_null, flatbuffers_bool, flatbuffers_bool_t, 1, 1, UINT8_C(0), __pointer_pubkey)
__flatbuffers_build_table_field(1, flatbuffers_, __pointer_pubkey___data, pubkey, __pointer_pubkey)

static inline __pointer_pubkey_ref_t __pointer_pubkey_create(flatbuffers_builder_t *B ____pointer_pubkey_formal_args)
{
    if (__pointer_pubkey_start(B)
        || __pointer_pubkey___data_add(B, v1)
        || __pointer_pubkey___is_null_add(B, v0)) {
        return 0;
    }
    return __pointer_pubkey_end(B);
}

static __pointer_pubkey_ref_t __pointer_pubkey_clone(flatbuffers_builder_t *B, __pointer_pubkey_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (__pointer_pubkey_start(B)
        || __pointer_pubkey___data_pick(B, t)
        || __pointer_pubkey___is_null_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, __pointer_pubkey_end(B));
}

__flatbuffers_build_table_field(0, flatbuffers_, __ocall_wrapper_calc_message_msg, encl_message_t, __ocall_wrapper_calc_message)
__flatbuffers_build_table_field(1, flatbuffers_, __ocall_wrapper_calc_message___return_value, encl_message_t, __ocall_wrapper_calc_message)

static inline __ocall_wrapper_calc_message_ref_t __ocall_wrapper_calc_message_create(flatbuffers_builder_t *B ____ocall_wrapper_calc_message_formal_args)
{
    if (__ocall_wrapper_calc_message_start(B)
        || __ocall_wrapper_calc_message_msg_add(B, v0)
        || __ocall_wrapper_calc_message___return_value_add(B, v1)) {
        return 0;
    }
    return __ocall_wrapper_calc_message_end(B);
}

static __ocall_wrapper_calc_message_ref_t __ocall_wrapper_calc_message_clone(flatbuffers_builder_t *B, __ocall_wrapper_calc_message_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (__ocall_wrapper_calc_message_start(B)
        || __ocall_wrapper_calc_message_msg_pick(B, t)
        || __ocall_wrapper_calc_message___return_value_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, __ocall_wrapper_calc_message_end(B));
}

__flatbuffers_build_table_field(0, flatbuffers_, __ocall_wrapper_get_attestation_report___return_value, report, __ocall_wrapper_get_attestation_report)

static inline __ocall_wrapper_get_attestation_report_ref_t __ocall_wrapper_get_attestation_report_create(flatbuffers_builder_t *B ____ocall_wrapper_get_attestation_report_formal_args)
{
    if (__ocall_wrapper_get_attestation_report_start(B)
        || __ocall_wrapper_get_attestation_report___return_value_add(B, v0)) {
        return 0;
    }
    return __ocall_wrapper_get_attestation_report_end(B);
}

static __ocall_wrapper_get_attestation_report_ref_t __ocall_wrapper_get_attestation_report_clone(flatbuffers_builder_t *B, __ocall_wrapper_get_attestation_report_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (__ocall_wrapper_get_attestation_report_start(B)
        || __ocall_wrapper_get_attestation_report___return_value_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, __ocall_wrapper_get_attestation_report_end(B));
}

__flatbuffers_build_vector_field(0, flatbuffers_, __ocall_wrapper_print_buffer_str, flatbuffers_int8, int8_t, __ocall_wrapper_print_buffer)
__flatbuffers_build_scalar_field(1, flatbuffers_, __ocall_wrapper_print_buffer___return_value, flatbuffers_uint32, uint32_t, 4, 4, UINT32_C(0), __ocall_wrapper_print_buffer)

static inline __ocall_wrapper_print_buffer_ref_t __ocall_wrapper_print_buffer_create(flatbuffers_builder_t *B ____ocall_wrapper_print_buffer_formal_args)
{
    if (__ocall_wrapper_print_buffer_start(B)
        || __ocall_wrapper_print_buffer_str_add(B, v0)
        || __ocall_wrapper_print_buffer___return_value_add(B, v1)) {
        return 0;
    }
    return __ocall_wrapper_print_buffer_end(B);
}

static __ocall_wrapper_print_buffer_ref_t __ocall_wrapper_print_buffer_clone(flatbuffers_builder_t *B, __ocall_wrapper_print_buffer_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (__ocall_wrapper_print_buffer_start(B)
        || __ocall_wrapper_print_buffer_str_pick(B, t)
        || __ocall_wrapper_print_buffer___return_value_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, __ocall_wrapper_print_buffer_end(B));
}

__flatbuffers_build_scalar_field(0, flatbuffers_, __ocall_wrapper_print_value_val, flatbuffers_uint32, uint32_t, 4, 4, UINT32_C(0), __ocall_wrapper_print_value)
__flatbuffers_build_scalar_field(1, flatbuffers_, __ocall_wrapper_print_value___return_value, flatbuffers_int8, int8_t, 1, 1, INT8_C(0), __ocall_wrapper_print_value)

static inline __ocall_wrapper_print_value_ref_t __ocall_wrapper_print_value_create(flatbuffers_builder_t *B ____ocall_wrapper_print_value_formal_args)
{
    if (__ocall_wrapper_print_value_start(B)
        || __ocall_wrapper_print_value_val_add(B, v0)
        || __ocall_wrapper_print_value___return_value_add(B, v1)) {
        return 0;
    }
    return __ocall_wrapper_print_value_end(B);
}

static __ocall_wrapper_print_value_ref_t __ocall_wrapper_print_value_clone(flatbuffers_builder_t *B, __ocall_wrapper_print_value_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (__ocall_wrapper_print_value_start(B)
        || __ocall_wrapper_print_value_val_pick(B, t)
        || __ocall_wrapper_print_value___return_value_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, __ocall_wrapper_print_value_end(B));
}

__flatbuffers_build_table_field(0, flatbuffers_, __ocall_wrapper_set_client_pk_pk, __pointer_pubkey, __ocall_wrapper_set_client_pk)
__flatbuffers_build_scalar_field(1, flatbuffers_, __ocall_wrapper_set_client_pk___return_value, flatbuffers_int32, int32_t, 4, 4, INT32_C(0), __ocall_wrapper_set_client_pk)

static inline __ocall_wrapper_set_client_pk_ref_t __ocall_wrapper_set_client_pk_create(flatbuffers_builder_t *B ____ocall_wrapper_set_client_pk_formal_args)
{
    if (__ocall_wrapper_set_client_pk_start(B)
        || __ocall_wrapper_set_client_pk_pk_add(B, v0)
        || __ocall_wrapper_set_client_pk___return_value_add(B, v1)) {
        return 0;
    }
    return __ocall_wrapper_set_client_pk_end(B);
}

static __ocall_wrapper_set_client_pk_ref_t __ocall_wrapper_set_client_pk_clone(flatbuffers_builder_t *B, __ocall_wrapper_set_client_pk_table_t t)
{
    __flatbuffers_memoize_begin(B, t);
    if (__ocall_wrapper_set_client_pk_start(B)
        || __ocall_wrapper_set_client_pk_pk_pick(B, t)
        || __ocall_wrapper_set_client_pk___return_value_pick(B, t)) {
        return 0;
    }
    __flatbuffers_memoize_end(B, t, __ocall_wrapper_set_client_pk_end(B));
}

#include "flatcc/flatcc_epilogue.h"
#endif /* OCALLS_BUILDER_H */
