#include "Message.hpp"
#include <format>
#include <ctime>
#include <cstring>

std::string Message::getEncryptedAsHexString() const
{
    std::stringstream ss;

    for (unsigned char byte : encryptedMessage)
    {
        ss << std::hex
           << std::setw(2)
           << std::setfill('0')
           << (int)byte;
    }

    return ss.str();
}

std::string Message::getTimestampAsString() const
{
    std::time_t timeSeconds = static_cast<std::time_t>(this->timestamp);
    std::tm *data = std::gmtime(&timeSeconds);

    return std::format("{:04d}-{:02d}-{:02d} {:02d}:{:02d}:{:02d}",
                       data->tm_year + 1900,
                       data->tm_mon + 1,
                       data->tm_mday,
                       data->tm_hour,
                       data->tm_min,
                       data->tm_sec);
}

std::vector<uint8_t> Message::serialize() const
{
    std::vector<uint8_t> buffer;

    uint32_t vecSize = static_cast<uint32_t>(encryptedMessage.size());

    size_t totalSize = sizeof(type) + sizeof(vecSize) + sizeof(senderId) + sizeof(receiverId) + sizeof(timestamp) + vecSize;
    buffer.resize(totalSize);

    size_t offset = 0;

    std::memcpy(buffer.data() + offset, &type, sizeof(type));
    offset += sizeof(type);
    std::memcpy(buffer.data() + offset, &vecSize, sizeof(vecSize));
    offset += sizeof(vecSize);
    std::memcpy(buffer.data() + offset, &senderId, sizeof(senderId));
    offset += sizeof(senderId);
    std::memcpy(buffer.data() + offset, &receiverId, sizeof(receiverId));
    offset += sizeof(receiverId);
    std::memcpy(buffer.data() + offset, &timestamp, sizeof(timestamp));
    offset += sizeof(timestamp);

    std::memcpy(buffer.data() + offset, encryptedMessage.data(), vecSize);

    return buffer;
}

Message Message::deserialize(const std::vector<uint8_t> &buffer)
{
    if (buffer.size() < 20) {
        return Message(TEXT_MESSAGE, {}, 0, 0, 0);
    }

    uint8_t rawType = 0;
    uint32_t vecSize = 0;
    int32_t sId = 0;
    int32_t rId = 0;
    int64_t tStamp = 0;
    std::vector<uint8_t> encMsg;

    size_t offset = 0;

    std::memcpy(&rawType, buffer.data() + offset, sizeof(rawType));                     offset += sizeof(rawType);
    std::memcpy(&vecSize, buffer.data() + offset, sizeof(vecSize));               offset += sizeof(vecSize);
    std::memcpy(&sId, buffer.data() + offset, sizeof(sId));                       offset += sizeof(sId);
    std::memcpy(&rId, buffer.data() + offset, sizeof(rId));                       offset += sizeof(rId);
    std::memcpy(&tStamp, buffer.data() + offset, sizeof(tStamp));                 offset += sizeof(tStamp);

    if (buffer.size() >= offset + vecSize) {
        encMsg.resize(vecSize);
        std::memcpy(encMsg.data(), buffer.data() + offset, vecSize);
    }

    return Message(static_cast<MessageType>(rawType), encMsg, sId, rId, tStamp);
}