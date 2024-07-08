//
// Generated file, do not edit! Created by nedtool 6.0 from veins/modules/application/blockchain/PoWPackingPermission.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "veins\modules\application\blockchain\PoWPackingPermission_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace veins {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule to generate operator<< for shared_ptr<T>
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const std::shared_ptr<T>& t) { return out << t.get(); }

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline typename std::enable_if<!std::is_base_of<omnetpp::cObject, T>::value, std::ostream&>::type
operator<<(std::ostream& out,const T&) {const char *s = omnetpp::opp_typename(typeid(T)); out.put('<'); out.write(s, strlen(s)); out.put('>'); return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');

    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(PoWPackingPermission)

PoWPackingPermission::PoWPackingPermission(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

PoWPackingPermission::PoWPackingPermission(const PoWPackingPermission& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

PoWPackingPermission::~PoWPackingPermission()
{
}

PoWPackingPermission& PoWPackingPermission::operator=(const PoWPackingPermission& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void PoWPackingPermission::copy(const PoWPackingPermission& other)
{
    this->rsuId = other.rsuId;
    this->hash = other.hash;
    this->nonce = other.nonce;
    this->blockData = other.blockData;
    this->timestamp = other.timestamp;
    this->difficultyLevel = other.difficultyLevel;
}

void PoWPackingPermission::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->rsuId);
    doParsimPacking(b,this->hash);
    doParsimPacking(b,this->nonce);
    doParsimPacking(b,this->blockData);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->difficultyLevel);
}

void PoWPackingPermission::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->rsuId);
    doParsimUnpacking(b,this->hash);
    doParsimUnpacking(b,this->nonce);
    doParsimUnpacking(b,this->blockData);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->difficultyLevel);
}

int PoWPackingPermission::getRsuId() const
{
    return this->rsuId;
}

void PoWPackingPermission::setRsuId(int rsuId)
{
    this->rsuId = rsuId;
}

const char * PoWPackingPermission::getHash() const
{
    return this->hash.c_str();
}

void PoWPackingPermission::setHash(const char * hash)
{
    this->hash = hash;
}

int PoWPackingPermission::getNonce() const
{
    return this->nonce;
}

void PoWPackingPermission::setNonce(int nonce)
{
    this->nonce = nonce;
}

const char * PoWPackingPermission::getBlockData() const
{
    return this->blockData.c_str();
}

void PoWPackingPermission::setBlockData(const char * blockData)
{
    this->blockData = blockData;
}

omnetpp::simtime_t PoWPackingPermission::getTimestamp() const
{
    return this->timestamp;
}

void PoWPackingPermission::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

int PoWPackingPermission::getDifficultyLevel() const
{
    return this->difficultyLevel;
}

void PoWPackingPermission::setDifficultyLevel(int difficultyLevel)
{
    this->difficultyLevel = difficultyLevel;
}

class PoWPackingPermissionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_rsuId,
        FIELD_hash,
        FIELD_nonce,
        FIELD_blockData,
        FIELD_timestamp,
        FIELD_difficultyLevel,
    };
  public:
    PoWPackingPermissionDescriptor();
    virtual ~PoWPackingPermissionDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(PoWPackingPermissionDescriptor)

PoWPackingPermissionDescriptor::PoWPackingPermissionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::PoWPackingPermission)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

PoWPackingPermissionDescriptor::~PoWPackingPermissionDescriptor()
{
    delete[] propertyNames;
}

bool PoWPackingPermissionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PoWPackingPermission *>(obj)!=nullptr;
}

const char **PoWPackingPermissionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PoWPackingPermissionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PoWPackingPermissionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int PoWPackingPermissionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_rsuId
        FD_ISEDITABLE,    // FIELD_hash
        FD_ISEDITABLE,    // FIELD_nonce
        FD_ISEDITABLE,    // FIELD_blockData
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_difficultyLevel
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *PoWPackingPermissionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "rsuId",
        "hash",
        "nonce",
        "blockData",
        "timestamp",
        "difficultyLevel",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int PoWPackingPermissionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "rsuId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "hash") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "nonce") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "blockData") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "difficultyLevel") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *PoWPackingPermissionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_rsuId
        "string",    // FIELD_hash
        "int",    // FIELD_nonce
        "string",    // FIELD_blockData
        "omnetpp::simtime_t",    // FIELD_timestamp
        "int",    // FIELD_difficultyLevel
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **PoWPackingPermissionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PoWPackingPermissionDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PoWPackingPermissionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PoWPackingPermissionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PoWPackingPermission'", field);
    }
}

const char *PoWPackingPermissionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PoWPackingPermissionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        case FIELD_rsuId: return long2string(pp->getRsuId());
        case FIELD_hash: return oppstring2string(pp->getHash());
        case FIELD_nonce: return long2string(pp->getNonce());
        case FIELD_blockData: return oppstring2string(pp->getBlockData());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        case FIELD_difficultyLevel: return long2string(pp->getDifficultyLevel());
        default: return "";
    }
}

void PoWPackingPermissionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        case FIELD_rsuId: pp->setRsuId(string2long(value)); break;
        case FIELD_hash: pp->setHash((value)); break;
        case FIELD_nonce: pp->setNonce(string2long(value)); break;
        case FIELD_blockData: pp->setBlockData((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        case FIELD_difficultyLevel: pp->setDifficultyLevel(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoWPackingPermission'", field);
    }
}

omnetpp::cValue PoWPackingPermissionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        case FIELD_rsuId: return pp->getRsuId();
        case FIELD_hash: return pp->getHash();
        case FIELD_nonce: return pp->getNonce();
        case FIELD_blockData: return pp->getBlockData();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        case FIELD_difficultyLevel: return pp->getDifficultyLevel();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PoWPackingPermission' as cValue -- field index out of range?", field);
    }
}

void PoWPackingPermissionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        case FIELD_rsuId: pp->setRsuId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hash: pp->setHash(value.stringValue()); break;
        case FIELD_nonce: pp->setNonce(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_blockData: pp->setBlockData(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_difficultyLevel: pp->setDifficultyLevel(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoWPackingPermission'", field);
    }
}

const char *PoWPackingPermissionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr PoWPackingPermissionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PoWPackingPermissionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PoWPackingPermission *pp = omnetpp::fromAnyPtr<PoWPackingPermission>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoWPackingPermission'", field);
    }
}

}  // namespace veins

namespace omnetpp {

}  // namespace omnetpp

