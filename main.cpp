#include "Post.h"
#include <iostream>
#include <iomanip>
#include <regex>
#include <queue>
#include <string>
#include <vector>
#include <fstream>
#include <map>

// Function to create each of the 3 meta objects: musicMeta, authorMeta, and videoMeta when parsing json file
std::map<std::string, std::string> createMeta(size_t& pos, const std::string& json_content) {
    // Initialize an empty map to store key-value pairs
    std::map<std::string, std::string> meta;

    // Continue parsing until the end of the JSON-like content is reached
    while (json_content[pos] != '}') {
        // Initialize variables to store the key and value for the current pair
        std::string key;
        std::string value;

        // Move the position indicator to skip the opening quote and potential white spaces
        pos = pos + 2;

        // Parse the key until the colon is encountered
        while (json_content[pos] != ':') {
            // Exclude double quotes from the key
            if (json_content[pos] != '"') {
                key += json_content[pos];
            }
            // Move to the next character
            pos++;
        }

        // Move the position indicator to skip the colon and potential white spaces
        pos = pos + 2;

        // Check if the key is "signature"
        if (key == "signature") {
            // Move to skip the opening quote for the value
            pos++;

            // Parse the value until the closing quote is encountered
            while (json_content[pos] != '"') {
                value += json_content[pos];
                // Move to the next character
                pos++;
            }
        }
        // If the key is not "signature", parse the value until a comma or the end of the object
        else {
            while (json_content[pos] != ',' && json_content[pos] != '}') {
                // Exclude double quotes from the value
                if (json_content[pos] != '"') {
                    value += json_content[pos];
                }
                // Move to the next character
                pos++;
            }
        }

        // Insert the key-value pair into the map
        meta.insert({key, value});
    }

    // Return the populated map
    return meta;
}

// Reading in and parsing input json file
std::vector<Post> readJsonFile(const std::string& inputFile) {
    // Vector to store Post objects parsed from the JSON file
    std::vector<Post> posts;

    // Open the input JSON file
    std::ifstream jsonFile(inputFile);
    if (!jsonFile.is_open()) {
        // Display an error message and exit if the file cannot be opened
        std::cerr << "Failed to open the JSON file." << std::endl;
        exit(1);
    }

    // Read the entire content of the JSON file into a string
    std::string json_content;
    std::string line;
    while (std::getline(jsonFile, line)) {
        json_content += line;
    }
    // Close the file as its content is read into json_content
    jsonFile.close();

    // Find the position of the first colon in the JSON content
    size_t pos = json_content.find(':');

    // Loop to find and parse each comment in the JSON content
    while (pos != std::string::npos ) {
        // Vector to store parsed values for each comment
        std::vector<std::string> output(13);
        std::map<std::string, std::string> authorMeta;
        std::map<std::string, std::string> musicMeta;
        std::map<std::string, std::string> videoMeta;

        // Iterate over the expected 13 values for each comment
        for (int i = 0; i < 13; i++) {
            pos = pos + 2;

            // Extract values until a comma or a closing brace (for the last value)
            if (i < 4 || i == 6 || i > 7) {
                if (i != 1 && i != 12) {
                    // Parse values excluding double quotes
                    while (json_content[pos] != ',' && json_content[pos] != '}') {
                        if (json_content[pos] != '"') {
                            output[i] += json_content[pos];
                        }
                        pos++;
                    }
                }
                else if (i != 12){
                    // Handle special case for values enclosed in double quotes
                    pos++;
                    while (json_content[pos] != '"') {
                        output[i] += json_content[pos];
                        pos++;
                    }
                }
                else {
                    // Parse the last value until the closing brace
                    while (json_content[pos] != '}') {
                        output[i] += json_content[pos];
                        pos++;
                    }
                }
            }

                // Parse authorMeta
            else if (i == 4) {
                authorMeta = createMeta(pos, json_content);
            }

                // Parse musicMeta
            else if (i == 5) {
                musicMeta = createMeta(pos, json_content);
            }

                // Parse videoMeta
            else if (i == 7) {
                videoMeta = createMeta(pos, json_content);
            }

            // Find the position of the next colon for the next iteration
            pos = json_content.find(':', pos + 1);
        }

        // Create a Post object and add it to the vector
        posts.emplace_back(output[0], output[1], output[2], output[3], authorMeta,
                           musicMeta, output[6], videoMeta, std::stoi(output[8]),
                           std::stoi(output[9]), std::stoi(output[10]), std::stoi(output[11]), output[12]);
    }

    // Return the vector of parsed Post objects
    return posts;
}

// Function to find the hashtags and count the hashtag frequency
std::map<std::string, std::pair<int, double>> findTrendingHashtag(const std::vector<Post>& posts) {
    // Initialize variables to store post text and hashtag frequencies
    std::string text;
    std::map<std::string, std::pair<int, double>> hashtagFrequency;

    // Iterate through each Post in the vector
    for (const Post& post : posts) {
        // Get the text content of the post
        text = post.getText();

        // Define a regular expression to match hashtags
        std::regex hashtagRegex("#([\\w\\u0080-\\uFFFF]+)");

        // Create an iterator for matching using the defined regex
        std::sregex_iterator hashtagIterator(text.begin(), text.end(), hashtagRegex);
        std::sregex_iterator endIterator;

        // Iterate over the matches and extract the hashtags
        while (hashtagIterator != endIterator) {
            // Get the matched hashtag from the capturing group
            std::smatch match = *hashtagIterator;
            std::string hashtag = match.str(1);  // extract the first capturing group

            // Check if the hashtag is already present in the frequency map
            if (hashtagIterator != endIterator) {
                try {
                    // Update the frequency and total play count for an existing hashtag
                    hashtagFrequency.at('#' + hashtag) = {hashtagFrequency.at('#' + hashtag).first + 1,
                                                          hashtagFrequency.at('#' + hashtag).second + post.getPlayCount()};
                }
                    // Handle the case when the hashtag is not found in the map
                catch (std::out_of_range&) {
                    // Add a new entry for the hashtag with an initial frequency of 1 and the post's play count
                    hashtagFrequency['#' + hashtag] = {1, post.getPlayCount()};
                }
            }

            // Move to the next hashtag match
            ++hashtagIterator;
        }
    }

    // Return the map containing hashtag frequencies and total play counts
    return hashtagFrequency;
}

//comparing play count
struct ComparePosts {
    bool operator()(const Post& post1, const Post& post2) {
        return post1.getPlayCount() < post2.getPlayCount();
    }
};

//Function to find top posts for hashtags
std::vector<std::vector<Post>> findTopPosts(const std::vector<Post>& posts, const std::vector<std::string>& topTen) {
    std::vector<std::vector<Post>> topPosts(10);

    for (int i = 0; i < topTen.size(); i++) {
        // Priority queue to store the top posts based on play count
        std::priority_queue<Post, std::vector<Post>, ComparePosts> topPostsQueue;

        for (const Post& post : posts) {
            std::string text = post.getText();

            // Check if the post contains the current hashtag, is not already in the topPosts vector
            if (text.find(topTen[i]) != std::string::npos &&
                std::find(topPosts[i].begin(), topPosts[i].end(), post) == topPosts[i].end()) {

                int occurrences = 0;
                size_t pos = 0;

                while ((pos = text.find(topTen[i], pos)) != std::string::npos) {
                    if (text[pos + topTen[i].size()] == std::string::npos || !std::isalpha(text[pos + topTen[i].size()])) {
                        occurrences++;
                    }

                    pos += topTen[i].size();
                }

                while (occurrences > 0) {
                    // Enqueue the post in the priority queue
                    topPostsQueue.push(post);
                    occurrences--;
                }
            }
        }

        // Pop the top 3 posts from the priority queue and store them in the result vector
        for (int j = 0; j < 3 && !topPostsQueue.empty(); j++) {
            topPosts[i].push_back(topPostsQueue.top());
            topPostsQueue.pop();
        }
    }

    return topPosts;
}

// Function to find the top ten hashtags
std::vector<std::string> findTopTen(std::map<std::string, std::pair<int, double>> hashtags) {
    // Initialize a vector to store the top ten hashtags
    std::vector<std::string> topTen;

    // Iterate up to 10 times or until all hashtags are considered
    for (int i = 0; i < 10 && i < hashtags.size(); i++) {
        // Temporary variables to store the current top hashtag, frequency, and view count
        std::string hashtag;
        int count = 0;
        int viewCount = 0;

        // Iterate through the map of hashtags
        for (std::map<std::string, std::pair<int, double>>::iterator it = hashtags.begin(); it != hashtags.end(); ++it) {
            // Check if the hashtag is not in the current topTen and has a higher frequency
            if (std::find(topTen.begin(), topTen.end(), it->first) == topTen.end() && it->second.first != count) {
                // Update the temporary variables if the frequency is higher
                if (it->second.first > count) {
                    hashtag = it->first;
                    count = it->second.first;
                    viewCount = it->second.second;
                }
            }
                // Check if the hashtag is not in the current topTen and has a higher view count
            else if (std::find(topTen.begin(), topTen.end(), it->first) == topTen.end() && it->second.second != viewCount) {
                // Update the temporary variables if the view count is higher
                if (it->second.second > viewCount) {
                    hashtag = it->first;
                    count = it->second.first;
                    viewCount = it->second.second;
                }
            }
                // Check if the hashtag is not in the current topTen and has a lexicographically smaller name
            else if (std::find(topTen.begin(), topTen.end(), it->first) == topTen.end() && it->first < hashtag) {
                // Update the temporary variables based on lexicographical order
                hashtag = it->first;
                count = it->second.first;
                viewCount = it->second.second;
            }
        }

        // Add the current top hashtag to the vector of top ten hashtags
        if (!hashtag.empty()) {
            topTen.push_back(hashtag);
        }
    }

    // Return the vector containing the top ten hashtags
    return topTen;
}

// Function to print the hashtag to the output file
void printHashtag(std::vector<std::vector<Post>>& topPosts, const std::map<std::string, std::pair<int, double>>& hashtags, const std::vector<std::string>& topTen, const std::string& outputFile) {
    std::ofstream output(outputFile);

    output << "trending hashtags:" << std::endl << std::endl;
    for (int i = 0; i < topTen.size(); i++) {
        output << "========================" << std::endl;
        output << topTen[i] << std::endl;
        output << "used " << hashtags.at(topTen[i]).first << " times" << std::endl;
        output << std::fixed << std::setprecision(0) << hashtags.at(topTen[i]).second << " views" << std::endl << std::endl;
        for (int j = 0; j < topPosts[i].size(); j++) {
            output << "cover url: " << topPosts[i][j].getVideoMeta().at("coverUrl") << std::endl;
            output << "web video url: " << topPosts[i][j].getWebVideoUrl() << std::endl;
        }

        output << "========================" << std::endl;
    }

    output.close();
}

// Function to find the sounds and count the sound frequency
std::map<std::string, std::pair<int, double>> findTrendingSounds(const std::vector<Post>& posts) {
    // Initialize variables to store music ID and sound frequencies
    std::string musicId;
    std::map<std::string, std::pair<int, double>> soundFrequency;

    // Iterate through each Post in the vector
    for (const Post& post : posts) {
        try {
            // Try to get the music ID from the music metadata of the post
            musicId = post.getMusicMeta()["musicId"];

            // Check if the music ID is already present in the frequency map
            try {
                // Update the frequency and total play count for an existing music ID
                soundFrequency.at(musicId) = {soundFrequency.at(musicId).first + 1, soundFrequency.at(musicId).second + post.getPlayCount()};
            }
                // Handle the case when the music ID is not found in the map
            catch (std::out_of_range&) {
                // Add a new entry for the music ID with an initial frequency of 1 and the post's play count
                soundFrequency[musicId] = {1, post.getPlayCount()};
            }
        }
            // Handle the case when the music ID is not found in the music metadata
        catch (std::out_of_range&) {
            // Continue to the next post
            continue;
        }
    }

    // Return the map containing music ID frequencies and total play counts
    return soundFrequency;
}

// Finds the top three posts for each sound in the provided vector of posts based on play count and associates them in a two-dimensional vector.
std::vector<std::vector<Post>> findTopSounds(const std::vector<Post>& posts, const std::vector<std::string>& topTen) {
    // Initialize a two-dimensional vector to store the top posts for each sound
    std::vector<std::vector<Post>> topPosts(10);

    // Iterate over each sound in the topTen vector
    for (int i = 0; i < topTen.size(); i++) {
        // Temporary variables to store the current sound's music ID and count
        std::string musicId;

        // Iterate three times to find the top three posts for each sound
        for (int j = 0; j < 3; j++) {
            // Temporary Post object to store the current top post
            Post temp;

            // Count variable to track the play count of the current top post
            int count = 0;

            // Iterate over each post in the provided vector of posts
            for (const Post& post : posts) {
                try {
                    // Attempt to retrieve the music ID from the music metadata of the post
                    musicId = post.getMusicMeta()["musicId"];
                }
                catch (std::out_of_range&) {
                    // Continue to the next post if the music ID is not found
                    continue;
                }

                // Check if the post is associated with the current sound (music ID)
                // and if it is not already in the topPosts vector, and if it has a higher play count than the current top post
                if (musicId.find(topTen[i]) != std::string::npos &&
                    std::find(topPosts[i].begin(), topPosts[i].end(), post) == topPosts[i].end() &&
                    temp.getPlayCount() < post.getPlayCount()) {
                    // Update the temporary variables with the information from the current post
                    temp = post;
                    count = temp.getPlayCount();
                }
            }

            // If a top post is found, add it to the topPosts vector for the current sound
            if (count != 0) {
                topPosts[i].push_back(temp);
            }
        }
    }

    // Return the two-dimensional vector containing the top three posts for each sound
    return topPosts;
}

// Function to find the top ten sounds
std::vector<std::string> findTopTenSounds(std::map<std::string, std::pair<int, double>> sounds) {
    // Vector to store the top ten music IDs
    std::vector<std::string> topTen;

    // Iterate up to 10 times or until all music IDs are considered
    for (int i = 0; i < 10 && i < sounds.size(); i++) {
        // Temporary variables to store the current top music ID, frequency, and view count
        std::string musicId;
        int count = 0;
        int viewCount = 0;

        // Iterate through the map of music IDs and their frequencies
        for (std::map<std::string, std::pair<int, double>>::iterator it = sounds.begin(); it != sounds.end(); ++it) {
            // Check if the music ID is not in the current topTen and has a higher view count
            if (std::find(topTen.begin(), topTen.end(), it->first) == topTen.end() && it->second.second != viewCount) {
                // Update the temporary variables if the view count is higher
                if (it->second.second > viewCount) {
                    musicId = it->first;
                    count = it->second.first;
                    viewCount = it->second.second;
                }
            }
                // Check if the music ID is not in the current topTen and has a higher frequency
            else if (std::find(topTen.begin(), topTen.end(), it->first) == topTen.end() && it->second.first != count) {
                // Update the temporary variables if the frequency is higher
                if (it->second.first > count) {
                    musicId = it->first;
                    count = it->second.first;
                    viewCount = it->second.second;
                }
            }
                // Check if the music ID is not in the current topTen and has a lexicographically smaller name
            else if (std::find(topTen.begin(), topTen.end(), it->first) == topTen.end() && it->first < musicId) {
                // Update the temporary variables based on lexicographical order
                musicId = it->first;
                count = it->second.first;
                viewCount = it->second.second;
            }
        }

        // Add the current top music ID to the vector of top ten music IDs
        if (!musicId.empty()) {
            topTen.push_back(musicId);
        }
    }

    // Return the vector containing the top ten music IDs
    return topTen;
}

// Function to print the sound to the output file
void printSounds(std::vector<std::vector<Post>>& topPosts, const std::map<std::string, std::pair<int, double>>& sounds, const std::vector<std::string>& topTen, const std::string& outputFile) {
    std::ofstream output(outputFile);

    output << "trending sounds:" << std::endl << std::endl;
    for (int i = 0; i < topTen.size(); i++) {
        std::map<std::string, std::string> musicMeta = topPosts[i][0].getMusicMeta();
        output << "========================" << std::endl;
        output << musicMeta["musicName"] << std::endl;
        output << std::fixed << std::setprecision(0) << sounds.at(topTen[i]).second << " views" << std::endl;
        output << musicMeta["musicAuthor"] << std::endl;
        output << "music id: " << topTen[i] << std::endl << std::endl;
        for (int j = 0; j < topPosts[i].size(); j++) {
            output << "cover url: " << topPosts[i][j].getVideoMeta().at("coverUrl") << std::endl;
            output << "web video url: " << topPosts[i][j].getWebVideoUrl() << std::endl;
        }

        output << "========================" << std::endl;
    }

    output.close();
}

int main(int argc, char* argv[]) {
    // Check if the required command-line arguments are provided
    if (argc < 4) {
        // Print usage instructions and exit with an error code
        std::cerr << "Usage: " << argv[0] << " jsonFile outputFileName tag" << std::endl;
        return 1;
    }

    // Extract command-line arguments
    std::string jsonFile = argv[1];          // JSON file containing data collected from TikTok
    std::string outputFileName = argv[2];     // The name of the output HTML file
    std::string tag = argv[3];                // Specify either "hashtag" or "sound"

    std::vector<Post> posts;
    std::vector<std::string> topTen;
    std::vector<std::vector<Post>> topPosts;

    // Read TikTok data from the JSON file
    posts = readJsonFile(jsonFile);

    // Process data based on the specified tag (hashtag or sound)
    if (tag == "hashtag") {
        // Find trending hashtags and associated posts
        std::map<std::string, std::pair<int, double>> hashtags = findTrendingHashtag(posts);
        topTen = findTopTen(hashtags);
        topPosts = findTopPosts(posts, topTen);

        // Generate and print output HTML for hashtags
        printHashtag(topPosts, hashtags, topTen, outputFileName);
    } else if (tag == "sound") {
        // Find trending sounds and associated posts
        std::map<std::string, std::pair<int, double>> sounds = findTrendingSounds(posts);
        topTen = findTopTenSounds(sounds);
        topPosts = findTopSounds(posts, topTen);

        // Generate and print output HTML for sounds
        printSounds(topPosts, sounds, topTen, outputFileName);
    } else {
        // Handle invalid tag argument
        std::cerr << "Invalid argument." << std::endl;
    }

    // Return 0 to indicate successful execution
    return 0;
}