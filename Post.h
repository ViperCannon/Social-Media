#ifndef HW9_POST_H
#define HW9_POST_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Post {
public:
    //default constructor
    Post();
    //parametrized constructor
    Post(const std::string& id, const std::string& text, const std::string& createTime, const std::string& createTimeISO,
           const  std::map<std::string, std::string>& authorMeta, const  std::map<std::string, std::string>& musicMeta,
           const std::string& webVideoUrl, const  std::map<std::string, std::string>& videoMeta,
           const int& diggCount, const int& shareCount, const double& playCount, const int& commentCount,
           const std::string& mentions);

    //Accessors
    std::string getId() const;
    std::string getText() const;
    std::string getCreateTime() const;
    std::string getCreateTimeISO() const;
    std::map<std::string, std::string> getAuthorMeta() const;
    std::map<std::string, std::string> getMusicMeta() const;
    std::string getWebVideoUrl() const;
    std::map<std::string, std::string> getVideoMeta() const;
    int getDiggCount() const;
    int getShareCount() const;
    double getPlayCount() const;
    int getCommentCount() const;
    std::string getMentions() const;

    //Modifiers
    void setId(std::string aId);
    void setText(std::string aText);
    void setCreateTime(std::string aCreateTime);
    void setCreateTimeISO(std::string aCreateTimeISO);
    void setAuthorMeta( std::map<std::string, std::string> aAuthorMeta);
    void setMusicMeta( std::map<std::string, std::string> aMusicMeta);
    void setWebVideoUrl(std::string aWebVideoUrl);
    void setVideoMeta( std::map<std::string, std::string> aVideoMeta);
    void setDiggCount(int aDiggCount);
    void setShareCount(int aShareCount);
    void setPlayCount(double aPlayCount);
    void setCommentCount(int aCommentCount);
    void setMentions(std::string aMentions);

    bool operator>(const Post& other) const;
    bool operator<(const Post& other) const;

private:
    //member variables
    std::string id;
    std::string text;
    std::string createTime;
    std::string createTimeISO;
    std::map<std::string, std::string> authorMeta;
    std::map<std::string, std::string> musicMeta;
    std::string webVideoUrl;
    std::map<std::string, std::string> videoMeta;
    int diggCount;
    int shareCount;
    double playCount;
    int commentCount;
    std::string mentions;
};

//overloaded operator to compare two objects
bool operator==(const Post& a, const Post& b);

#endif //HW9_POST_H
