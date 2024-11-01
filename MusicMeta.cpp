#include "MusicMeta.h"
#include <iostream>

//default constructor
MusicMeta::MusicMeta() {
    musicName = "";
    musicAuthor = "";
    musicOriginal = false;
    playUrl = "";
    coverMediumUrl = "";
    musicId = "";
}

//parametrized constructor
MusicMeta::MusicMeta(const std::string& musicName, const std::string& musicAuthor, const bool musicOriginal,
                     const std::string& playUrl, const std::string& coverMediumUrl, const std::string& musicId) {
    this->musicName = musicName;
    this->musicAuthor = musicAuthor;
    this->musicOriginal = musicOriginal; //bool
    this->playUrl = playUrl;
    this->coverMediumUrl = coverMediumUrl;
    this->musicId = musicId;
}

//getter functions
std::string MusicMeta::getMusicName() const {
    return musicName;
}
std::string MusicMeta::getMusicAuthor() const {
    return musicAuthor;
}
bool MusicMeta::getMusicOriginal() const {
    return musicOriginal;
}
std::string MusicMeta::getPlayUrl() const {
    return playUrl;
}
std::string MusicMeta::getCoverMediumUrl() const {
    return coverMediumUrl;
}
std::string MusicMeta::getMusicId() const {
    return musicId;
}

//setter functions
void MusicMeta::setMusicName(std::string aMusicName) {
    musicName = aMusicName;
}
void MusicMeta::setMusicAuthor(std::string aMusicAuthor) {
    musicAuthor = aMusicAuthor;
}
void MusicMeta::setMusicOriginal(bool aMusicOriginal) {
    musicOriginal = aMusicOriginal;
}
void MusicMeta::setPlayUrl(std::string aPlayUrl) {
    playUrl = aPlayUrl;
}
void MusicMeta::setCoverMediumUrl(std::string aCoverMediumUrl) {
    coverMediumUrl = aCoverMediumUrl;
}
void MusicMeta::setMusicId(std::string aMusicId) {
    musicId = aMusicId;
}
