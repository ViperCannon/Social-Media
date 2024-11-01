#include "Post.h"
#include <iostream>

//default constructor
Post::Post() {
    id = "";
    text = "";
    createTime = "";
    createTimeISO = "";
    webVideoUrl = "";
    diggCount = 0;
    shareCount = 0;
    playCount = 0;
    commentCount = 0;
    mentions = "";
}

//parametrized constructor
Post::Post(const std::string& id, const std::string& text, const std::string& createTime, const std::string& createTimeISO,
           const  std::map<std::string, std::string>& authorMeta, const  std::map<std::string, std::string>& musicMeta,
           const std::string& webVideoUrl, const  std::map<std::string, std::string>& videoMeta,
           const int& diggCount, const int& shareCount, const double& playCount, const int& commentCount,
           const std::string& mentions) {
    this->id = id;
    this->text = text;
    this->createTime = createTime;
    this->createTimeISO = createTimeISO;
    this->webVideoUrl = webVideoUrl;
    this->diggCount = diggCount;
    this->shareCount = shareCount;
    this->playCount = playCount;
    this->commentCount = commentCount;
    this->mentions = mentions;
    this->authorMeta = authorMeta;
    this->videoMeta = videoMeta;
    this->musicMeta = musicMeta;
}

//getter functions
std::string Post::getId() const {
    return id;
}
std::string Post::getText() const {
    return text;
}
std::string Post::getCreateTime() const {
    return createTime;
}
std::string Post::getCreateTimeISO() const {
    return createTimeISO;
}
std::map<std::string, std::string> Post::getAuthorMeta() const {
    return authorMeta;
}
std::map<std::string, std::string> Post::getMusicMeta() const {
    return musicMeta;
}
std::string Post::getWebVideoUrl() const {
    return webVideoUrl;
}
std::map<std::string, std::string> Post::getVideoMeta() const {
    return videoMeta;
}
int Post::getDiggCount() const {
    return diggCount;
}
int Post::getShareCount() const {
    return shareCount;
}
double Post::getPlayCount() const {
    return playCount;
}
int Post::getCommentCount() const {
    return commentCount;
}
std::string Post::getMentions() const {
    return mentions;
}

//setter functions
void Post::setId(std::string aId) {
    id = aId;
}
void Post::setText(std::string aText) {
    text = aText;
}
void Post::setCreateTime(std::string aCreateTime) {
    createTime = aCreateTime;
}
void Post::setCreateTimeISO(std::string aCreateTimeISO) {
    createTimeISO = aCreateTimeISO;
}
void Post::setAuthorMeta( std::map<std::string, std::string> aAuthorMeta) {
    authorMeta = aAuthorMeta;
}
void Post::setMusicMeta( std::map<std::string, std::string> aMusicMeta) {
    musicMeta = aMusicMeta;
}
void Post::setWebVideoUrl(std::string aWebVideoUrl) {
    webVideoUrl = aWebVideoUrl;
}
void Post::setVideoMeta( std::map<std::string, std::string> aVideoMeta) {
    videoMeta = aVideoMeta;
}
void Post::setDiggCount(int aDiggCount) {
    diggCount = aDiggCount;
}
void Post::setShareCount(int aShareCount) {
    shareCount = aShareCount;
}
void Post::setPlayCount(double aPlayCount) {
    playCount = aPlayCount;
}
void Post::setCommentCount(int aCommentCount) {
    commentCount = aCommentCount;
}
void Post::setMentions(std::string aMentions) {
    mentions = aMentions;
}

//overloaded operator to compare two objects
bool operator==(const Post& a, const Post& b) {
    // Compare each member variable for equality
    return a.getId() == b.getId() &&
           a.getText() == b.getText() &&
           a.getCreateTime() == b.getCreateTime() &&
           a.getCreateTimeISO() == b.getCreateTimeISO() &&
           a.getAuthorMeta() == b.getAuthorMeta() &&
           a.getMusicMeta() == b.getMusicMeta() &&
           a.getWebVideoUrl() == b.getWebVideoUrl() &&
           a.getVideoMeta() == b.getVideoMeta() &&
           a.getDiggCount() == b.getDiggCount() &&
           a.getShareCount() == b.getShareCount() &&
           a.getPlayCount() == b.getPlayCount() &&
           a.getCommentCount() == b.getCommentCount() &&
           a.getMentions() == b.getMentions();
}

// Overloaded greater-than operator for Post objects, comparing them based on play count.
bool Post::operator>(const Post& other) const {
    return this->getPlayCount() > other.getPlayCount();
}

// Overloaded less-than operator for Post objects, comparing them based on play count.
bool Post::operator<(const Post& other) const {
    return this->getPlayCount() < other.getPlayCount();
}