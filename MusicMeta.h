#ifndef HW9_MUSICMETA_H
#define HW9_MUSICMETA_H

#include <iostream>
#include <string>
#include <vector>

class MusicMeta {
public:
    //default constructor
    MusicMeta();
    //parametrized constructor
    MusicMeta(const std::string& musicName, const std::string& musicAuthor, const bool musicOriginal,
         const std::string& playUrl, const std::string& coverMediumUrl, const std::string& musicId);

    //Accessors
    std::string getMusicName() const;
    std::string getMusicAuthor() const;
    bool getMusicOriginal() const;
    std::string getPlayUrl() const;
    std::string getCoverMediumUrl() const;
    std::string getMusicId() const;

    //Modifiers
    void setMusicName(std::string aMusicName);
    void setMusicAuthor(std::string aMusicAuthor);
    void setMusicOriginal(bool aMusicOriginal);
    void setPlayUrl(std::string aPlayUrl);
    void setCoverMediumUrl(std::string aCoverMediumUrl);
    void setMusicId(std::string aMusicId);

private:
    //member variables
    std::string musicName;
    std::string musicAuthor;
    bool musicOriginal;
    std::string playUrl;
    std::string coverMediumUrl;
    std::string musicId;

};
//overloaded output stream operator for printing Matching Documents of Website objects
//std::ostream& operator<<(std::ostream& out, const MusicMeta& website);

#endif //HW9_MUSICMETA_H
