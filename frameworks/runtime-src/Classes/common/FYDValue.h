

#ifndef __FYD_VALUE__
#define __FYD_VALUE__

#include <string>
#include <vector>
#include <unordered_map>
#include <float.h>
#include "FYDHeaders.h"

NS_FYD_BEGIN
    
class Value;

typedef std::vector<Value> ValueVector;
typedef std::unordered_map<std::string, Value> ValueMap;
typedef std::unordered_map<int, Value> ValueMapIntKey;

/*
 * 提供一些基本数据类型,以及数组、字典类型的包装,提供一个统一的类型
 */
class Value
{
public:
    /** 默认构造函数 */
    Value();
    
    /** 包装无符号字符类型 */
    explicit Value(unsigned char v);
    
    /** 包装整形 */
    explicit Value(int v);

    /** 包装无符号整形 */
    explicit Value(unsigned int v);

    /** 包装浮点类型 */
    explicit Value(float v);
    
    /** 包装双精度浮点型 */
    explicit Value(double v);
    
    /** 包装布尔类型 */
    explicit Value(bool v);
    
    /** 包装字符型 */
    explicit Value(const char* v);
    
    /** 包装字符串型 */
    explicit Value(const std::string& v);
    
    /** 包装Value数组 类型 */
    explicit Value(const ValueVector& v);
    /** 包装Value数组类型 std::move 的形式   
     将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝 
     所以使用的时候需要注意销毁内存的时候不要重复销毁
     */
    explicit Value(ValueVector&& v);
    
    /** 包装Value字典 类型 */
    explicit Value(const ValueMap& v);
    /** 包装Value字典 类型 std::move 的形式 */
    explicit Value(ValueMap&& v);
    
    /** 包装Value字典,这种字典以整形数字作为key */
    explicit Value(const ValueMapIntKey& v);
    /** 包装Value字典,这种字典以整形数字作为key std::move 的形式 */
    explicit Value(ValueMapIntKey&& v);

    /** 根据另一个Value 来创建一个新的对象 */
    Value(const Value& other);
    /** 根据另一个Value 来创建一个新的对象 std::move的形式 */
    Value(Value&& other);
    
    /** 析构函数 */
    ~Value();

    /** 操作符重载 赋值操作 Value to Value. */
    Value& operator= (const Value& other);
    /** 操作符重载 赋值操作 Value to Value. It will use std::move internally. */
    Value& operator= (Value&& other);

    /** 操作符重载 赋值操作 unsigned char to Value. */
    Value& operator= (unsigned char v);
    /** 操作符重载 赋值操作 integer to Value. */
    Value& operator= (int v);
    /** 操作符重载 赋值操作 integer to Value. */
    Value& operator= (unsigned int v);
    /** 操作符重载 赋值操作 float to Value. */
    Value& operator= (float v);
    /** 操作符重载 赋值操作 double to Value. */
    Value& operator= (double v);
    /** 操作符重载 赋值操作 bool to Value. */
    Value& operator= (bool v);
    /** 操作符重载 赋值操作 char* to Value. */
    Value& operator= (const char* v);
    /** 操作符重载 赋值操作 string to Value. */
    Value& operator= (const std::string& v);

    /** 操作符重载 赋值操作 ValueVector to Value. */
    Value& operator= (const ValueVector& v);
    /** 操作符重载 赋值操作 ValueVector to Value. */
    Value& operator= (ValueVector&& v);

    /** 操作符重载 赋值操作 ValueMap to Value. */
    Value& operator= (const ValueMap& v);
    /** 操作符重载 赋值操作 ValueMap to Value. It will use std::move internally. */
    Value& operator= (ValueMap&& v);

    /** 操作符重载 赋值操作 ValueMapIntKey to Value. */
    Value& operator= (const ValueMapIntKey& v);
    /** 操作符重载 赋值操作 ValueMapIntKey to Value. It will use std::move internally. */
    Value& operator= (ValueMapIntKey&& v);

    /** != 等号 不等号判断 */
    bool operator!= (const Value& v);
    /** != 等号 不等号判断 */
    bool operator!= (const Value& v) const;
    /** == 等号 不等号判断 */
    bool operator== (const Value& v);
    /** == 等号 不等号判断 */
    bool operator== (const Value& v) const;

    /** 转换成无符号字节流返回 */
    unsigned char asByte() const;
    /** 转换为整形返回 */
    int asInt() const;
    /** 转换为无符号整形返回 */
    unsigned int asUnsignedInt() const;
    /** 转换为浮点数返回 */
    float asFloat() const;
    /** 转换为双精度浮点类型 */
    double asDouble() const;
    /** 转换成布尔类型 */
    bool asBool() const;
    /** 转换成字符串类型 */
    std::string asString() const;

    /** 转换成Value数组类型 */
    ValueVector& asValueVector();
    /** 常函数 转换Value数组类型 */
    const ValueVector& asValueVector() const;

    /** 转换Value字典类型 */
    ValueMap& asValueMap();
    /** 常函数 转换Value字典类型 */
    const ValueMap& asValueMap() const;

    /** 转换Value字典类型  整形作为key值的字典 */
    ValueMapIntKey& asIntKeyMap();
    /** 常函数 转换Value字典类型  整形作为key值的字典 */
    const ValueMapIntKey& asIntKeyMap() const;

    /**
     * 检查Value值是否为空
     */
    bool isNull() const { return _type == Type::NONE; }

    /** Value type wrapped by Value. */
    enum class Type
    {
        /// no value is wrapped, an empty Value
        NONE = 0,
        /// wrap byte
        BYTE,
        /// wrap integer
        INTEGER,
        /// wrap unsigned
        UNSIGNED,
        /// wrap float
        FLOAT,
        /// wrap double
        DOUBLE,
        /// wrap bool
        BOOLEAN,
        /// wrap string
        STRING,
        /// wrap vector
        VECTOR,
        /// wrap ValueMap
        MAP,
        /// wrap ValueMapIntKey
        INT_KEY_MAP
    };

    /** 获取Value的类型 */
    Type getType() const { return _type; }

    /** 输出一个Value的值,如果Value是Map或者Vector则递归输出值 */
    std::string getDescription() const;

private:
    void clear();
    void reset(Type type);
    /* 共用体 用来存储数据的地方 */
    union
    {
        unsigned char byteVal;
        int intVal;
        unsigned int unsignedVal;
        float floatVal;
        double doubleVal;
        bool boolVal;

        std::string* strVal;
        ValueVector* vectorVal;
        ValueMap* mapVal;
        ValueMapIntKey* intKeyMapVal;
    }_field;
    /* Value 类型 的值的数据类型*/
    Type _type;
};

NS_FYD_ENDED


#endif
