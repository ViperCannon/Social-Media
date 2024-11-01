#include "VideoMeta.h"
#include <iostream>

//default constructor
VideoMeta::VideoMeta() {
    height = 0;
    width = 0;
    duration = 0;
    coverUrl = "";
    definition = "";
    format = "";
    downloadAddr = "";
}

//parametrized constructor
VideoMeta::VideoMeta(const int& height, const int& width, const int& duration, const std::string& coverUrl,
                     const std::string& definition, const std::string& format, const std::string& downloadAddr) {
    this->height = height;
    this->width = width;
    this->duration = duration;
    this->coverUrl = coverUrl;
    this->definition = definition;
    this->format = format;
    this->downloadAddr = downloadAddr;
}

//getter functions
int VideoMeta::getHeight() const {
    return height;
}
int VideoMeta::getWidth() const {
    return width;
}
int VideoMeta::getDuration() const {
    return duration;
}
std::string VideoMeta::getCoverUrl() const {
    return coverUrl;
}
std::string VideoMeta::getDefinition() const {
    return definition;
}
std::string VideoMeta::getFormat() const {
    return format;
}
std::string VideoMeta::getDownloadAddr() const {
    return downloadAddr;
}

//setter functions
void VideoMeta::setHeight(int aHeight) {
    height = aHeight;
}
void VideoMeta::setWidth(int aWidth) {
    width = aWidth;
}
void VideoMeta::setDuration(int aDuration) {
    duration = aDuration;
}
void VideoMeta::setCoverUrl(std::string aCoverUrl) {
    coverUrl = aCoverUrl;
}
void VideoMeta::setDefinition(std::string aDefinition) {
    definition = aDefinition;
}
void VideoMeta::setFormat(std::string aFormat) {
    format = aFormat;
}
void VideoMeta::setDownloadAddr(std::string aDownloadAddr) {
    downloadAddr = aDownloadAddr;
}
