//
// Generated file, do not edit! Created by nedtool 6.0 from veins/base/messages/AirFrame.msg.
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
#include "AirFrame_m.h"

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

Register_Class(AirFrame)

AirFrame::AirFrame(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

AirFrame::AirFrame(const AirFrame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

AirFrame::~AirFrame()
{
}

AirFrame& AirFrame::operator=(const AirFrame& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void AirFrame::copy(const AirFrame& other)
{
    this->signal = other.signal;
    this->poa = other.poa;
    this->duration = other.duration;
    this->state = other.state;
    this->type = other.type;
    this->id = other.id;
    this->protocolId = other.protocolId;
    this->channel = other.channel;
    this->mcs = other.mcs;
}

void AirFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->signal);
    doParsimPacking(b,this->poa);
    doParsimPacking(b,this->duration);
    doParsimPacking(b,this->state);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->id);
    doParsimPacking(b,this->protocolId);
    doParsimPacking(b,this->channel);
    doParsimPacking(b,this->mcs);
}

void AirFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->signal);
    doParsimUnpacking(b,this->poa);
    doParsimUnpacking(b,this->duration);
    doParsimUnpacking(b,this->state);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->id);
    doParsimUnpacking(b,this->protocolId);
    doParsimUnpacking(b,this->channel);
    doParsimUnpacking(b,this->mcs);
}

const Signal& AirFrame::getConstSignal() const
{
    return this->signal;
}

void AirFrame::setSignal(const Signal& signal)
{
    this->signal = signal;
}

const POA& AirFrame::getConstPoa() const
{
    return this->poa;
}

void AirFrame::setPoa(const POA& poa)
{
    this->poa = poa;
}

omnetpp::simtime_t AirFrame::getDuration() const
{
    return this->duration;
}

void AirFrame::setDuration(omnetpp::simtime_t duration)
{
    this->duration = duration;
}

int AirFrame::getState() const
{
    return this->state;
}

void AirFrame::setState(int state)
{
    this->state = state;
}

int AirFrame::getType() const
{
    return this->type;
}

void AirFrame::setType(int type)
{
    this->type = type;
}

long AirFrame::getId() const
{
    return this->id;
}

void AirFrame::setId(long id)
{
    this->id = id;
}

int AirFrame::getProtocolId() const
{
    return this->protocolId;
}

void AirFrame::setProtocolId(int protocolId)
{
    this->protocolId = protocolId;
}

int AirFrame::getChannel() const
{
    return this->channel;
}

void AirFrame::setChannel(int channel)
{
    this->channel = channel;
}

int AirFrame::getMcs() const
{
    return this->mcs;
}

void AirFrame::setMcs(int mcs)
{
    this->mcs = mcs;
}

class AirFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_signal,
        FIELD_poa,
        FIELD_duration,
        FIELD_state,
        FIELD_type,
        FIELD_id,
        FIELD_protocolId,
        FIELD_channel,
        FIELD_mcs,
    };
  public:
    AirFrameDescriptor();
    virtual ~AirFrameDescriptor();

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

Register_ClassDescriptor(AirFrameDescriptor)

AirFrameDescriptor::AirFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(veins::AirFrame)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

AirFrameDescriptor::~AirFrameDescriptor()
{
    delete[] propertyNames;
}

bool AirFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<AirFrame *>(obj)!=nullptr;
}

const char **AirFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *AirFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int AirFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 9+base->getFieldCount() : 9;
}

unsigned int AirFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_signal
        0,    // FIELD_poa
        FD_ISEDITABLE,    // FIELD_duration
        FD_ISEDITABLE,    // FIELD_state
        FD_ISEDITABLE,    // FIELD_type
        FD_ISEDITABLE,    // FIELD_id
        FD_ISEDITABLE,    // FIELD_protocolId
        FD_ISEDITABLE,    // FIELD_channel
        FD_ISEDITABLE,    // FIELD_mcs
    };
    return (field >= 0 && field < 9) ? fieldTypeFlags[field] : 0;
}

const char *AirFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "signal",
        "poa",
        "duration",
        "state",
        "type",
        "id",
        "protocolId",
        "channel",
        "mcs",
    };
    return (field >= 0 && field < 9) ? fieldNames[field] : nullptr;
}

int AirFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "signal") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "poa") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "duration") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "state") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "id") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "protocolId") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "channel") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "mcs") == 0) return baseIndex + 8;
    return base ? base->findField(fieldName) : -1;
}

const char *AirFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "veins::Signal",    // FIELD_signal
        "veins::POA",    // FIELD_poa
        "omnetpp::simtime_t",    // FIELD_duration
        "int",    // FIELD_state
        "int",    // FIELD_type
        "long",    // FIELD_id
        "int",    // FIELD_protocolId
        "int",    // FIELD_channel
        "int",    // FIELD_mcs
    };
    return (field >= 0 && field < 9) ? fieldTypeStrings[field] : nullptr;
}

const char **AirFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_signal: {
            static const char *names[] = { "getter", "getterForUpdate",  nullptr };
            return names;
        }
        case FIELD_poa: {
            static const char *names[] = { "getter", "getterForUpdate",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *AirFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_signal:
            if (!strcmp(propertyName, "getter")) return "getConstSignal";
            if (!strcmp(propertyName, "getterForUpdate")) return "getSignal";
            return nullptr;
        case FIELD_poa:
            if (!strcmp(propertyName, "getter")) return "getConstPoa";
            if (!strcmp(propertyName, "getterForUpdate")) return "getPoa";
            return nullptr;
        default: return nullptr;
    }
}

int AirFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void AirFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'AirFrame'", field);
    }
}

const char *AirFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string AirFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        case FIELD_signal: {std::stringstream out; out << pp->getConstSignal(); return out.str();}
        case FIELD_poa: {std::stringstream out; out << pp->getConstPoa(); return out.str();}
        case FIELD_duration: return simtime2string(pp->getDuration());
        case FIELD_state: return long2string(pp->getState());
        case FIELD_type: return long2string(pp->getType());
        case FIELD_id: return long2string(pp->getId());
        case FIELD_protocolId: return long2string(pp->getProtocolId());
        case FIELD_channel: return long2string(pp->getChannel());
        case FIELD_mcs: return long2string(pp->getMcs());
        default: return "";
    }
}

void AirFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        case FIELD_duration: pp->setDuration(string2simtime(value)); break;
        case FIELD_state: pp->setState(string2long(value)); break;
        case FIELD_type: pp->setType(string2long(value)); break;
        case FIELD_id: pp->setId(string2long(value)); break;
        case FIELD_protocolId: pp->setProtocolId(string2long(value)); break;
        case FIELD_channel: pp->setChannel(string2long(value)); break;
        case FIELD_mcs: pp->setMcs(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AirFrame'", field);
    }
}

omnetpp::cValue AirFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        case FIELD_signal: return omnetpp::toAnyPtr(&pp->getConstSignal()); break;
        case FIELD_poa: return omnetpp::toAnyPtr(&pp->getConstPoa()); break;
        case FIELD_duration: return pp->getDuration().dbl();
        case FIELD_state: return pp->getState();
        case FIELD_type: return pp->getType();
        case FIELD_id: return (omnetpp::intval_t)(pp->getId());
        case FIELD_protocolId: return pp->getProtocolId();
        case FIELD_channel: return pp->getChannel();
        case FIELD_mcs: return pp->getMcs();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'AirFrame' as cValue -- field index out of range?", field);
    }
}

void AirFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        case FIELD_duration: pp->setDuration(value.doubleValue()); break;
        case FIELD_state: pp->setState(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_type: pp->setType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_id: pp->setId(omnetpp::checked_int_cast<long>(value.intValue())); break;
        case FIELD_protocolId: pp->setProtocolId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_channel: pp->setChannel(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_mcs: pp->setMcs(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AirFrame'", field);
    }
}

const char *AirFrameDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr AirFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        case FIELD_signal: return omnetpp::toAnyPtr(&pp->getConstSignal()); break;
        case FIELD_poa: return omnetpp::toAnyPtr(&pp->getConstPoa()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void AirFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    AirFrame *pp = omnetpp::fromAnyPtr<AirFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'AirFrame'", field);
    }
}

}  // namespace veins

namespace omnetpp {

}  // namespace omnetpp

