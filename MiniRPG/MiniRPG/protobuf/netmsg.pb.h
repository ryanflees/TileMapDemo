// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: netmsg.proto

#ifndef PROTOBUF_netmsg_2eproto__INCLUDED
#define PROTOBUF_netmsg_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace MessageCode {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_netmsg_2eproto();
void protobuf_AssignDesc_netmsg_2eproto();
void protobuf_ShutdownFile_netmsg_2eproto();

class ProtoLoginReq;
class ProtoLoginRes;
class ProtoEnterMapReq;
class ProtoEnterMapRes;
class ProtoNPCStatus;
class ProtoPlayerMoveReq;
class ProtoPlayerMoveRes;

enum ProtoNPCStatus_NPCDirection {
  ProtoNPCStatus_NPCDirection_P_LEFT = 1,
  ProtoNPCStatus_NPCDirection_P_RIGHT = 2,
  ProtoNPCStatus_NPCDirection_P_DOWN = 3,
  ProtoNPCStatus_NPCDirection_P_UP = 4
};
bool ProtoNPCStatus_NPCDirection_IsValid(int value);
const ProtoNPCStatus_NPCDirection ProtoNPCStatus_NPCDirection_NPCDirection_MIN = ProtoNPCStatus_NPCDirection_P_LEFT;
const ProtoNPCStatus_NPCDirection ProtoNPCStatus_NPCDirection_NPCDirection_MAX = ProtoNPCStatus_NPCDirection_P_UP;
const int ProtoNPCStatus_NPCDirection_NPCDirection_ARRAYSIZE = ProtoNPCStatus_NPCDirection_NPCDirection_MAX + 1;

const ::google::protobuf::EnumDescriptor* ProtoNPCStatus_NPCDirection_descriptor();
inline const ::std::string& ProtoNPCStatus_NPCDirection_Name(ProtoNPCStatus_NPCDirection value) {
  return ::google::protobuf::internal::NameOfEnum(
    ProtoNPCStatus_NPCDirection_descriptor(), value);
}
inline bool ProtoNPCStatus_NPCDirection_Parse(
    const ::std::string& name, ProtoNPCStatus_NPCDirection* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ProtoNPCStatus_NPCDirection>(
    ProtoNPCStatus_NPCDirection_descriptor(), name, value);
}
// ===================================================================

class ProtoLoginReq : public ::google::protobuf::Message {
 public:
  ProtoLoginReq();
  virtual ~ProtoLoginReq();

  ProtoLoginReq(const ProtoLoginReq& from);

  inline ProtoLoginReq& operator=(const ProtoLoginReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProtoLoginReq& default_instance();

  void Swap(ProtoLoginReq* other);

  // implements Message ----------------------------------------------

  ProtoLoginReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoLoginReq& from);
  void MergeFrom(const ProtoLoginReq& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 authID = 1;
  inline bool has_authid() const;
  inline void clear_authid();
  static const int kAuthIDFieldNumber = 1;
  inline ::google::protobuf::int32 authid() const;
  inline void set_authid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MessageCode.ProtoLoginReq)
 private:
  inline void set_has_authid();
  inline void clear_has_authid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 authid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_netmsg_2eproto();
  friend void protobuf_AssignDesc_netmsg_2eproto();
  friend void protobuf_ShutdownFile_netmsg_2eproto();

  void InitAsDefaultInstance();
  static ProtoLoginReq* default_instance_;
};
// -------------------------------------------------------------------

class ProtoLoginRes : public ::google::protobuf::Message {
 public:
  ProtoLoginRes();
  virtual ~ProtoLoginRes();

  ProtoLoginRes(const ProtoLoginRes& from);

  inline ProtoLoginRes& operator=(const ProtoLoginRes& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProtoLoginRes& default_instance();

  void Swap(ProtoLoginRes* other);

  // implements Message ----------------------------------------------

  ProtoLoginRes* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoLoginRes& from);
  void MergeFrom(const ProtoLoginRes& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 mapID = 1;
  inline bool has_mapid() const;
  inline void clear_mapid();
  static const int kMapIDFieldNumber = 1;
  inline ::google::protobuf::int32 mapid() const;
  inline void set_mapid(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MessageCode.ProtoLoginRes)
 private:
  inline void set_has_mapid();
  inline void clear_has_mapid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 mapid_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_netmsg_2eproto();
  friend void protobuf_AssignDesc_netmsg_2eproto();
  friend void protobuf_ShutdownFile_netmsg_2eproto();

  void InitAsDefaultInstance();
  static ProtoLoginRes* default_instance_;
};
// -------------------------------------------------------------------

class ProtoEnterMapReq : public ::google::protobuf::Message {
 public:
  ProtoEnterMapReq();
  virtual ~ProtoEnterMapReq();

  ProtoEnterMapReq(const ProtoEnterMapReq& from);

  inline ProtoEnterMapReq& operator=(const ProtoEnterMapReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProtoEnterMapReq& default_instance();

  void Swap(ProtoEnterMapReq* other);

  // implements Message ----------------------------------------------

  ProtoEnterMapReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoEnterMapReq& from);
  void MergeFrom(const ProtoEnterMapReq& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:MessageCode.ProtoEnterMapReq)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;


  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];

  friend void  protobuf_AddDesc_netmsg_2eproto();
  friend void protobuf_AssignDesc_netmsg_2eproto();
  friend void protobuf_ShutdownFile_netmsg_2eproto();

  void InitAsDefaultInstance();
  static ProtoEnterMapReq* default_instance_;
};
// -------------------------------------------------------------------

class ProtoEnterMapRes : public ::google::protobuf::Message {
 public:
  ProtoEnterMapRes();
  virtual ~ProtoEnterMapRes();

  ProtoEnterMapRes(const ProtoEnterMapRes& from);

  inline ProtoEnterMapRes& operator=(const ProtoEnterMapRes& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProtoEnterMapRes& default_instance();

  void Swap(ProtoEnterMapRes* other);

  // implements Message ----------------------------------------------

  ProtoEnterMapRes* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoEnterMapRes& from);
  void MergeFrom(const ProtoEnterMapRes& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 positinX = 1;
  inline bool has_positinx() const;
  inline void clear_positinx();
  static const int kPositinXFieldNumber = 1;
  inline ::google::protobuf::int32 positinx() const;
  inline void set_positinx(::google::protobuf::int32 value);

  // required int32 positinY = 2;
  inline bool has_positiny() const;
  inline void clear_positiny();
  static const int kPositinYFieldNumber = 2;
  inline ::google::protobuf::int32 positiny() const;
  inline void set_positiny(::google::protobuf::int32 value);

  // repeated .MessageCode.ProtoNPCStatus npcList = 3;
  inline int npclist_size() const;
  inline void clear_npclist();
  static const int kNpcListFieldNumber = 3;
  inline const ::MessageCode::ProtoNPCStatus& npclist(int index) const;
  inline ::MessageCode::ProtoNPCStatus* mutable_npclist(int index);
  inline ::MessageCode::ProtoNPCStatus* add_npclist();
  inline const ::google::protobuf::RepeatedPtrField< ::MessageCode::ProtoNPCStatus >&
      npclist() const;
  inline ::google::protobuf::RepeatedPtrField< ::MessageCode::ProtoNPCStatus >*
      mutable_npclist();

  // @@protoc_insertion_point(class_scope:MessageCode.ProtoEnterMapRes)
 private:
  inline void set_has_positinx();
  inline void clear_has_positinx();
  inline void set_has_positiny();
  inline void clear_has_positiny();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 positinx_;
  ::google::protobuf::int32 positiny_;
  ::google::protobuf::RepeatedPtrField< ::MessageCode::ProtoNPCStatus > npclist_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_netmsg_2eproto();
  friend void protobuf_AssignDesc_netmsg_2eproto();
  friend void protobuf_ShutdownFile_netmsg_2eproto();

  void InitAsDefaultInstance();
  static ProtoEnterMapRes* default_instance_;
};
// -------------------------------------------------------------------

class ProtoNPCStatus : public ::google::protobuf::Message {
 public:
  ProtoNPCStatus();
  virtual ~ProtoNPCStatus();

  ProtoNPCStatus(const ProtoNPCStatus& from);

  inline ProtoNPCStatus& operator=(const ProtoNPCStatus& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProtoNPCStatus& default_instance();

  void Swap(ProtoNPCStatus* other);

  // implements Message ----------------------------------------------

  ProtoNPCStatus* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoNPCStatus& from);
  void MergeFrom(const ProtoNPCStatus& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  typedef ProtoNPCStatus_NPCDirection NPCDirection;
  static const NPCDirection P_LEFT = ProtoNPCStatus_NPCDirection_P_LEFT;
  static const NPCDirection P_RIGHT = ProtoNPCStatus_NPCDirection_P_RIGHT;
  static const NPCDirection P_DOWN = ProtoNPCStatus_NPCDirection_P_DOWN;
  static const NPCDirection P_UP = ProtoNPCStatus_NPCDirection_P_UP;
  static inline bool NPCDirection_IsValid(int value) {
    return ProtoNPCStatus_NPCDirection_IsValid(value);
  }
  static const NPCDirection NPCDirection_MIN =
    ProtoNPCStatus_NPCDirection_NPCDirection_MIN;
  static const NPCDirection NPCDirection_MAX =
    ProtoNPCStatus_NPCDirection_NPCDirection_MAX;
  static const int NPCDirection_ARRAYSIZE =
    ProtoNPCStatus_NPCDirection_NPCDirection_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  NPCDirection_descriptor() {
    return ProtoNPCStatus_NPCDirection_descriptor();
  }
  static inline const ::std::string& NPCDirection_Name(NPCDirection value) {
    return ProtoNPCStatus_NPCDirection_Name(value);
  }
  static inline bool NPCDirection_Parse(const ::std::string& name,
      NPCDirection* value) {
    return ProtoNPCStatus_NPCDirection_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // required int32 npcID = 1;
  inline bool has_npcid() const;
  inline void clear_npcid();
  static const int kNpcIDFieldNumber = 1;
  inline ::google::protobuf::int32 npcid() const;
  inline void set_npcid(::google::protobuf::int32 value);

  // required int32 positinX = 2;
  inline bool has_positinx() const;
  inline void clear_positinx();
  static const int kPositinXFieldNumber = 2;
  inline ::google::protobuf::int32 positinx() const;
  inline void set_positinx(::google::protobuf::int32 value);

  // required int32 positinY = 3;
  inline bool has_positiny() const;
  inline void clear_positiny();
  static const int kPositinYFieldNumber = 3;
  inline ::google::protobuf::int32 positiny() const;
  inline void set_positiny(::google::protobuf::int32 value);

  // required .MessageCode.ProtoNPCStatus.NPCDirection direction = 4;
  inline bool has_direction() const;
  inline void clear_direction();
  static const int kDirectionFieldNumber = 4;
  inline ::MessageCode::ProtoNPCStatus_NPCDirection direction() const;
  inline void set_direction(::MessageCode::ProtoNPCStatus_NPCDirection value);

  // @@protoc_insertion_point(class_scope:MessageCode.ProtoNPCStatus)
 private:
  inline void set_has_npcid();
  inline void clear_has_npcid();
  inline void set_has_positinx();
  inline void clear_has_positinx();
  inline void set_has_positiny();
  inline void clear_has_positiny();
  inline void set_has_direction();
  inline void clear_has_direction();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 npcid_;
  ::google::protobuf::int32 positinx_;
  ::google::protobuf::int32 positiny_;
  int direction_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(4 + 31) / 32];

  friend void  protobuf_AddDesc_netmsg_2eproto();
  friend void protobuf_AssignDesc_netmsg_2eproto();
  friend void protobuf_ShutdownFile_netmsg_2eproto();

  void InitAsDefaultInstance();
  static ProtoNPCStatus* default_instance_;
};
// -------------------------------------------------------------------

class ProtoPlayerMoveReq : public ::google::protobuf::Message {
 public:
  ProtoPlayerMoveReq();
  virtual ~ProtoPlayerMoveReq();

  ProtoPlayerMoveReq(const ProtoPlayerMoveReq& from);

  inline ProtoPlayerMoveReq& operator=(const ProtoPlayerMoveReq& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProtoPlayerMoveReq& default_instance();

  void Swap(ProtoPlayerMoveReq* other);

  // implements Message ----------------------------------------------

  ProtoPlayerMoveReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoPlayerMoveReq& from);
  void MergeFrom(const ProtoPlayerMoveReq& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:MessageCode.ProtoPlayerMoveReq)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;


  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];

  friend void  protobuf_AddDesc_netmsg_2eproto();
  friend void protobuf_AssignDesc_netmsg_2eproto();
  friend void protobuf_ShutdownFile_netmsg_2eproto();

  void InitAsDefaultInstance();
  static ProtoPlayerMoveReq* default_instance_;
};
// -------------------------------------------------------------------

class ProtoPlayerMoveRes : public ::google::protobuf::Message {
 public:
  ProtoPlayerMoveRes();
  virtual ~ProtoPlayerMoveRes();

  ProtoPlayerMoveRes(const ProtoPlayerMoveRes& from);

  inline ProtoPlayerMoveRes& operator=(const ProtoPlayerMoveRes& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ProtoPlayerMoveRes& default_instance();

  void Swap(ProtoPlayerMoveRes* other);

  // implements Message ----------------------------------------------

  ProtoPlayerMoveRes* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ProtoPlayerMoveRes& from);
  void MergeFrom(const ProtoPlayerMoveRes& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:MessageCode.ProtoPlayerMoveRes)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;


  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[1];

  friend void  protobuf_AddDesc_netmsg_2eproto();
  friend void protobuf_AssignDesc_netmsg_2eproto();
  friend void protobuf_ShutdownFile_netmsg_2eproto();

  void InitAsDefaultInstance();
  static ProtoPlayerMoveRes* default_instance_;
};
// ===================================================================


// ===================================================================

// ProtoLoginReq

// required int32 authID = 1;
inline bool ProtoLoginReq::has_authid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProtoLoginReq::set_has_authid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProtoLoginReq::clear_has_authid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProtoLoginReq::clear_authid() {
  authid_ = 0;
  clear_has_authid();
}
inline ::google::protobuf::int32 ProtoLoginReq::authid() const {
  return authid_;
}
inline void ProtoLoginReq::set_authid(::google::protobuf::int32 value) {
  set_has_authid();
  authid_ = value;
}

// -------------------------------------------------------------------

// ProtoLoginRes

// required int32 mapID = 1;
inline bool ProtoLoginRes::has_mapid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProtoLoginRes::set_has_mapid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProtoLoginRes::clear_has_mapid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProtoLoginRes::clear_mapid() {
  mapid_ = 0;
  clear_has_mapid();
}
inline ::google::protobuf::int32 ProtoLoginRes::mapid() const {
  return mapid_;
}
inline void ProtoLoginRes::set_mapid(::google::protobuf::int32 value) {
  set_has_mapid();
  mapid_ = value;
}

// -------------------------------------------------------------------

// ProtoEnterMapReq

// -------------------------------------------------------------------

// ProtoEnterMapRes

// required int32 positinX = 1;
inline bool ProtoEnterMapRes::has_positinx() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProtoEnterMapRes::set_has_positinx() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProtoEnterMapRes::clear_has_positinx() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProtoEnterMapRes::clear_positinx() {
  positinx_ = 0;
  clear_has_positinx();
}
inline ::google::protobuf::int32 ProtoEnterMapRes::positinx() const {
  return positinx_;
}
inline void ProtoEnterMapRes::set_positinx(::google::protobuf::int32 value) {
  set_has_positinx();
  positinx_ = value;
}

// required int32 positinY = 2;
inline bool ProtoEnterMapRes::has_positiny() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProtoEnterMapRes::set_has_positiny() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProtoEnterMapRes::clear_has_positiny() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProtoEnterMapRes::clear_positiny() {
  positiny_ = 0;
  clear_has_positiny();
}
inline ::google::protobuf::int32 ProtoEnterMapRes::positiny() const {
  return positiny_;
}
inline void ProtoEnterMapRes::set_positiny(::google::protobuf::int32 value) {
  set_has_positiny();
  positiny_ = value;
}

// repeated .MessageCode.ProtoNPCStatus npcList = 3;
inline int ProtoEnterMapRes::npclist_size() const {
  return npclist_.size();
}
inline void ProtoEnterMapRes::clear_npclist() {
  npclist_.Clear();
}
inline const ::MessageCode::ProtoNPCStatus& ProtoEnterMapRes::npclist(int index) const {
  return npclist_.Get(index);
}
inline ::MessageCode::ProtoNPCStatus* ProtoEnterMapRes::mutable_npclist(int index) {
  return npclist_.Mutable(index);
}
inline ::MessageCode::ProtoNPCStatus* ProtoEnterMapRes::add_npclist() {
  return npclist_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::MessageCode::ProtoNPCStatus >&
ProtoEnterMapRes::npclist() const {
  return npclist_;
}
inline ::google::protobuf::RepeatedPtrField< ::MessageCode::ProtoNPCStatus >*
ProtoEnterMapRes::mutable_npclist() {
  return &npclist_;
}

// -------------------------------------------------------------------

// ProtoNPCStatus

// required int32 npcID = 1;
inline bool ProtoNPCStatus::has_npcid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProtoNPCStatus::set_has_npcid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProtoNPCStatus::clear_has_npcid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProtoNPCStatus::clear_npcid() {
  npcid_ = 0;
  clear_has_npcid();
}
inline ::google::protobuf::int32 ProtoNPCStatus::npcid() const {
  return npcid_;
}
inline void ProtoNPCStatus::set_npcid(::google::protobuf::int32 value) {
  set_has_npcid();
  npcid_ = value;
}

// required int32 positinX = 2;
inline bool ProtoNPCStatus::has_positinx() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProtoNPCStatus::set_has_positinx() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProtoNPCStatus::clear_has_positinx() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProtoNPCStatus::clear_positinx() {
  positinx_ = 0;
  clear_has_positinx();
}
inline ::google::protobuf::int32 ProtoNPCStatus::positinx() const {
  return positinx_;
}
inline void ProtoNPCStatus::set_positinx(::google::protobuf::int32 value) {
  set_has_positinx();
  positinx_ = value;
}

// required int32 positinY = 3;
inline bool ProtoNPCStatus::has_positiny() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ProtoNPCStatus::set_has_positiny() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ProtoNPCStatus::clear_has_positiny() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ProtoNPCStatus::clear_positiny() {
  positiny_ = 0;
  clear_has_positiny();
}
inline ::google::protobuf::int32 ProtoNPCStatus::positiny() const {
  return positiny_;
}
inline void ProtoNPCStatus::set_positiny(::google::protobuf::int32 value) {
  set_has_positiny();
  positiny_ = value;
}

// required .MessageCode.ProtoNPCStatus.NPCDirection direction = 4;
inline bool ProtoNPCStatus::has_direction() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ProtoNPCStatus::set_has_direction() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ProtoNPCStatus::clear_has_direction() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ProtoNPCStatus::clear_direction() {
  direction_ = 1;
  clear_has_direction();
}
inline ::MessageCode::ProtoNPCStatus_NPCDirection ProtoNPCStatus::direction() const {
  return static_cast< ::MessageCode::ProtoNPCStatus_NPCDirection >(direction_);
}
inline void ProtoNPCStatus::set_direction(::MessageCode::ProtoNPCStatus_NPCDirection value) {
  assert(::MessageCode::ProtoNPCStatus_NPCDirection_IsValid(value));
  set_has_direction();
  direction_ = value;
}

// -------------------------------------------------------------------

// ProtoPlayerMoveReq

// -------------------------------------------------------------------

// ProtoPlayerMoveRes


// @@protoc_insertion_point(namespace_scope)

}  // namespace MessageCode

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::MessageCode::ProtoNPCStatus_NPCDirection>() {
  return ::MessageCode::ProtoNPCStatus_NPCDirection_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_netmsg_2eproto__INCLUDED
