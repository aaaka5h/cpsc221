/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string &infile)
    : dict(256), filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold)
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
     Dict<string, int> hashTable(100000);
     while (infile.good()) {
         string word = infile.getNextWord();
         if (!hashTable.keyExists(word)) {
             hashTable.insert(word, 1);
         } else {
             int numTimes = hashTable.find(word);
             hashTable.remove(word);
             hashTable.insert(word, numTimes+1);
         }
     }

     typename Dict<string, int>::iterator it;
     for (it = hashTable.begin(); it != hashTable.end(); it++) {
         if (it->second >= threshold) ret.push_back(*it);
     }

    return ret;
}
