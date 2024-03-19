#pragma once
#include "vector"
#include "settings.h"
#include "AnalogFilter.h"

using user_t = int;

class FormatBase {
public:
    /**
     * Deserialize the array of bytes into the instance of this class
     * @param [in] in array of bytes
     */
    virtual void deserialize(const uint8_t* in) = 0;

    /**
     * Get size of this class after serialization
     */
    virtual size_t size() const = 0;

    /**
     * Serialize this class into the array of bytes
     */
    virtual void serialize(uint8_t* out) const = 0;
};

/**
 * Convert the array of bytes into the value of N-type.
 * @tparam N value type
 * @param [in] pArray the array of bytes
 * @return converted value
 */
template<typename N>
N ptov(const uint8_t * pArray) {
    const uint8_t sizeOfType = sizeof(N);
    auto temp = new uint8_t[sizeOfType]{};

    memcpy(temp, pArray, sizeOfType);
    N output = (*(N*)temp);
    delete[] temp;

    return output;
}

struct value_t: public FormatBase {
    user_t value = 0;
    size_t count = 0;

    explicit value_t(user_t value = 0) : count(1), value(value) {}

    const char* toString() const {
        static char out[20];
        sprintf(out, "value: %i | count: %zu", value, count);
        return out;
    }

    void deserialize(const uint8_t *in) override {
        value = ptov<user_t>(in);
        count = ptov<size_t>(&in[sizeof(value)]);
    }

    size_t size() const override {
        return sizeof(value) + sizeof(count);
    }

    void serialize(uint8_t *out) const override {
        memcpy(out, &this->value, sizeof(this->value));
        memcpy(&out[sizeof(this->value)], &this->count, sizeof(this->count));
    }
};

struct slice_t: public FormatBase {
    std::vector<value_t> array;

    void toString() const {
        for(const auto &i : this->array)
            Serial.println(i.toString());
    }

    void deserialize(const uint8_t *in) override {
        auto size = ptov<size_t>(in);
        size_t shift = sizeof(size);
        this->array.clear();

        for(size_t i = 0; i < size; i++) {
            value_t temp{};
            temp.deserialize(&in[shift]);
            this->array.push_back(temp);
            shift += temp.size();
        }
    }

    size_t size() const override {
        const value_t temp{};
        return sizeof(size_t) + this->array.size() * temp.size();
    }

    void serialize(uint8_t* out) const override {
        size_t size = this->array.size();
        memcpy(out, &size, sizeof(size));
        size_t shift = sizeof(size);

        for(const auto &i : this->array) {
            const size_t formatSize = i.size();
            auto pFormatRaw = new uint8_t [formatSize];
            i.serialize(pFormatRaw);

            memcpy(&out[shift], pFormatRaw, formatSize);
            shift += formatSize;
            delete[] pFormatRaw;
        }
    }
};

struct record_t: public FormatBase {
public:
    std::vector<slice_t> slices;

    record_t() {
//        this->addSlice();
    }

public:
    void addSlice() {
        slice_t slice{};
        this->slices.push_back(slice);
    }

    void addValue(user_t value) {
        slice_t& curSlice = getCurSlice();

        for(auto& i : curSlice.array) {
            if(i.value == value) {
                i.count++;
                return;
            }
        }

        value_t temp(value);
        curSlice.array.push_back(temp);
    }

    slice_t& getCurSlice() {
        return slices.back();
    }

    void toString() const {
        size_t sliceNum = 0;
        for(const auto& i : this->slices) {
            Serial.println((String)"Slice [" + sliceNum++ + "]:");
            i.toString();
            Serial.println("=======");
        }
    }

    void deserialize(const uint8_t *in) override {
        auto size = ptov<size_t>(in);
        size_t shift = sizeof(size);
        this->slices.clear();

        for(size_t i = 0; i < size; i++) {
            slice_t temp{};
            temp.deserialize(&in[shift]);
            this->slices.push_back(temp);
            shift += temp.size();
        }
    }

    size_t size() const override {
        size_t size = 0;
        for(const auto &i : this->slices)
            size += i.size();

        size += sizeof(size);
        return size;
    }

    void serialize(uint8_t* out) const override {
        size_t size = this->slices.size();
        memcpy(out, &size, sizeof(size));
        size_t shift = sizeof(size);

        for(const auto &i : this->slices) {
            const size_t formatSize = i.size();
            auto pFormatRaw = new uint8_t[formatSize];
            i.serialize(pFormatRaw);

            memcpy(&out[shift], pFormatRaw, formatSize);
            shift += formatSize;
            delete[] pFormatRaw;
        }
    }
};

extern record_t gRecord;

extern void IRAM_ATTR newSlice();

extern void setupTimer();

extern void startRecording(void *pvParameter);

extern void stopRecording();

extern void serialize(const record_t& record,
                      uint8_t** buf,
                      size_t& sizeOut,
                      uint64_t slicingT=0,
                      unsigned long duration=0);

extern void deserialize(record_t& record,
                        const uint8_t* buf,
                        uint64_t& slicingT,
                        unsigned long& duration);