//
// Generated file, do not edit! Created by nedtool 6.0 from veins/modules/application/blockchain/PoWResponse.msg.
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
#include "veins\modules\application\blockchain\PoWResponse_m.h"

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

Register_Class(PoWResponse)

PoWResponse::PoWResponse(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

PoWResponse::PoWResponse(const PoWResponse& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PoWResponse::~PoWResponse()
{
}

PoWResponse& PoWResponse::operator=(const PoWResponse& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PoWResponse::copy(const PoWResponse& other)
{
    this->data = other.data;
    this->hash = other.hash;
    this->nonce = other.nonce;
    this->timestamp = other.timestamp;
    this->difficultyLevel = other.difficultyLevel;
    this->byteLength = other.byteLength;
}

void PoWResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->data);
    doParsimPacking(b,this->hash);
    doParsimPacking(b,this->nonce);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->difficultyLevel);
    doParsimPacking(b,this->byteLength);
}

void PoWResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->data);
    doParsimUnpacking(b,this->hash);
    doParsimUnpacking(b,this->nonce);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->difficultyLevel);
    doParsimUnpacking(b,this->byteLength);
}

const char * PoWResponse::getData() const
{
    return this->data.c_str();
}

void PoWResponse::setData(const char * data)
{
    this->data = data;
}

const char * PoWResponse::getHash() const
{
    return this->hash.c_str();
}

void PoWResponse::setHash(const char * hash)
{
    this->hash = hash;
}

int PoWResponse::getNonce() const
{
    return this->nonce;
}

void PoWResponse::setNonce(int nonce)
{
    this->nonce = nonce;
}

omnetpp::simtime_t PoWResponse::getTimestamp() const
{
    return this->timestamp;
}

void PoWResponse::setTimestamp(omnetpp::simtime_t timestamp)
{
    this->timestamp = timestamp;
}

int PoWResponse::getDifficultyLevel() const
{
    return this->difficultyLevel;
}

void PoWResponse::setDifficultyLevel(int difficultyLevel)
{
    this->difficultyLevel = difficultyLevel;
}

int PoWResponse::getByteLength() const
{
    return this->byteLength;
}

void PoWResponse::setByteLength(int byteLength)
{
    this->byteLength = byteLength;
}

class PoWResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_data,
        FIELD_hash,
        FIELD_nonce,
        FIELD_timestamp,
        FIELD_difficultyLevel,
        FIELD_byteLength,
    };
  public:
    PoWResponseDescriptor();
    virtual ~PoWResponseDescriptor();

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

Register_ClassDescriptor(PoWResponseDescriptor)

PoWResponseDescriptor::PoWResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::PoWResponse)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

PoWResponseDescriptor::~PoWResponseDescriptor()
{
    delete[] propertyNames;
}

bool PoWResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PoWResponse *>(obj)!=nullptr;
}

const char **PoWResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PoWResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PoWResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int PoWResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_data
        FD_ISEDITABLE,    // FIELD_hash
        FD_ISEDITABLE,    // FIELD_nonce
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_difficultyLevel
        FD_ISEDITABLE,    // FIELD_byteLength
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *PoWResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "data",
        "hash",
        "nonce",
        "timestamp",
        "difficultyLevel",
        "byteLength",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int PoWResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "data") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "hash") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "nonce") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "difficultyLevel") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "byteLength") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *PoWResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_data
        "string",    // FIELD_hash
        "int",    // FIELD_nonce
        "omnetpp::simtime_t",    // FIELD_timestamp
        "int",    // FIELD_difficultyLevel
        "int",    // FIELD_byteLength
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **PoWResponseDescriptor::getFieldPropertyNames(int field) const
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

const char *PoWResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PoWResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PoWResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PoWResponse'", field);
    }
}

const char *PoWResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PoWResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        case FIELD_data: return oppstring2string(pp->getData());
        case FIELD_hash: return oppstring2string(pp->getHash());
        case FIELD_nonce: return long2string(pp->getNonce());
        case FIELD_timestamp: return simtime2string(pp->getTimestamp());
        case FIELD_difficultyLevel: return long2string(pp->getDifficultyLevel());
        case FIELD_byteLength: return long2string(pp->getByteLength());
        default: return "";
    }
}

void PoWResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        case FIELD_data: pp->setData((value)); break;
        case FIELD_hash: pp->setHash((value)); break;
        case FIELD_nonce: pp->setNonce(string2long(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2simtime(value)); break;
        case FIELD_difficultyLevel: pp->setDifficultyLevel(string2long(value)); break;
        case FIELD_byteLength: pp->setByteLength(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoWResponse'", field);
    }
}

omnetpp::cValue PoWResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        case FIELD_data: return pp->getData();
        case FIELD_hash: return pp->getHash();
        case FIELD_nonce: return pp->getNonce();
        case FIELD_timestamp: return pp->getTimestamp().dbl();
        case FIELD_difficultyLevel: return pp->getDifficultyLevel();
        case FIELD_byteLength: return pp->getByteLength();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PoWResponse' as cValue -- field index out of range?", field);
    }
}

void PoWResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        case FIELD_data: pp->setData(value.stringValue()); break;
        case FIELD_hash: pp->setHash(value.stringValue()); break;
        case FIELD_nonce: pp->setNonce(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_difficultyLevel: pp->setDifficultyLevel(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_byteLength: pp->setByteLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoWResponse'", field);
    }
}

const char *PoWResponseDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PoWResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PoWResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PoWResponse *pp = omnetpp::fromAnyPtr<PoWResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoWResponse'", field);
    }
}

}  // namespace veins

namespace omnetpp {

}  // namespace omnetpp

