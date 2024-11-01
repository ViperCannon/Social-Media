#ifndef HW9_VIDEOMETA_H
#define HW9_VIDEOMETA_H

#include <iostream>
#include <string>
#include <vector>

class VideoMeta {
public:
    //default constructor
    VideoMeta();
    //parametrized constructor
    VideoMeta(const int& height, const int& width, const int& duration, const std::string& coverUrl,
              const std::string& definition, const std::string& format, const std::string& downloadAddr);

    //Accessors
    int getHeight() const;
    int getWidth() const;
    int getDuration() const;
    std::string getCoverUrl() const;
    std::string getDefinition() const;
    std::string getFormat() const;
    std::string getDownloadAddr() const;

    //Modifiers
    void setHeight(int aHeight);
    void setWidth(int aWidth);
    void setDuration(int aDuration);
    void setCoverUrl(std::string aCoverUrl);
    void setDefinition(std::string aDefinition);
    void setFormat(std::string aFormat);
    void setDownloadAddr(std::string aDownloadAddr);

private:
    //member variables
    int height;
    int width;
    int duration;
    std::string coverUrl;
    std::string definition;
    std::string format;
    std::string downloadAddr;
};

#endif //HW9_VIDEOMETA_H
