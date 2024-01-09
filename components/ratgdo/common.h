#pragma once
#include <cstdint>
#include <functional>
#include "observable.h"

#define ESP_LOG1 ESP_LOGD
#define ESP_LOG2 ESP_LOGD


namespace esphome {
namespace ratgdo {

namespace protocol {

struct SetRollingCodeCounter { uint32_t counter; };
struct GetRollingCodeCounter {};
struct SetClientID { uint64_t client_id; };
struct QueryStatus{};
struct QueryOpenings{};


// a poor man's sum-type, because C++
class Args {
public:
    union {
       SetRollingCodeCounter set_rolling_code_counter;
       GetRollingCodeCounter get_rolling_code_counter;
       SetClientID set_client_id;
       QueryStatus query_status;
       QueryOpenings query_openings;
    } value;

    enum class Tag {
        set_rolling_code_counter,
        get_rolling_code_counter,
        set_client_id,
        query_status,
        query_openings,
    } tag;

    Args(GetRollingCodeCounter&& arg): tag(Tag::get_rolling_code_counter) {
        value.get_rolling_code_counter = std::move(arg);
    }
    Args(SetRollingCodeCounter&& arg): tag(Tag::set_rolling_code_counter) {
        value.set_rolling_code_counter = std::move(arg);
    }
    Args(SetClientID&& arg): tag(Tag::set_client_id) {
        value.set_client_id = std::move(arg);
    }
    Args(QueryStatus&& arg): tag(Tag::query_status) {
        value.query_status = std::move(arg);
    }
    Args(QueryOpenings&& arg): tag(Tag::query_openings) {
        value.query_openings = std::move(arg);
    }
};


struct RollingCodeCounter { observable<uint32_t>* value; };

class Result {
public:
    union {
       RollingCodeCounter rolling_code_counter;
    } value;

    enum class Tag {
        rolling_code_counter,
        void_,
    } tag;

    Result(): tag(Tag::void_) {
    }
    Result(RollingCodeCounter&& arg): tag(Tag::rolling_code_counter) {
        value.rolling_code_counter = std::move(arg);
    }
};

} // namespace protocol
} // namespace ratgdo
} // namespace esphome
