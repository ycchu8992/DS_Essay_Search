# Essay_Search 
109062110_DS_Final_Project_Essay_Search_Report

  一、編譯方式：

  我的 code 的編譯方式、測資的輸入，都與助教要求的相同，也就是

  ➢ g++ -std=c++17 -o essay-search.exe ./*.cpp -lstdc++fs

  ➢ ./essay_search.exe [input_folder_path] [query_file_path] [output_file_name]

  二、實作方式：

  以最初的 template 做修改，以便處理 query 每一行的 search command。

  這一部分的函式，處理（parse）讀進來的資料(data, query)的相關函式，
  放在Parser_Split.hpp。

  在 main.cpp 中，只會從 data 讀取一次資料(read_data)，然後，經過處理後，
  分別建成 for Exact and prefix 的 trie，以及 for Suffix 的trie。

  在 Trie 中，如果獨到抹個 TrieNode 時，剛好在 data 中，有字就是在
  此結尾，TrieNode 中的 is_word_end，就會是 true。

  然後因為在讀取 query時，就會判斷他是哪種類型的 search，會把它標出來，
  以 pair 的方式，存在一個 vector 中，所以在 search 每一個 data 的時候，
  就可以看他現在哪一種 search 來決定要 search 該 file 下的哪一個 tree。

  此外，因為有 and 以及 or 的 operator，所以在遇到 and 時，會從當前已經標示為
  true 的 data_file 的 tree，再去做 search，如果有找到，就維持該 file
  的標記為 true，否則就標記為 false。

  如果是 or，則會是在 false 的 datafile中尋找，因為最後他會會是聯集。

  在 query 中的一整行的 search command 都處理完後，就會對當前的所有 
  file 的標記，一個個做檢查，如果是true，就將該 data 的 
  title name push_back 進 vector 中，false 的話就把它復原成 ture。

  如果再所有 datafile2. Check 過一遍的情形下，沒有任何 title name 
  被加入，就將 Not Found!加進去。

  在後再關閉 query 後，在一次輸出。

  三、在過程中，碰到的挑戰

  在過程中，碰到比較大的問題有兩個。

  首先，因為要 traverse data 的資料夾，所以在查找資料，以及助教的公告後，
  選擇用<experimental/filesystem>。

  但因為我電腦 windows 的 gcc 版本是 8.1.0，根據網路上查到的資料，好想對
  這個版本而言，在 include<filesystem>(7.5.0不支援)，以及<experimental/filesystem>，
  都會碰到問題，而且我電腦上，並未有這些 file。按照自己所查的資料，解法有兩個，
  一個是將 windows 系統下的 gcc upgade 到 9.0.0 以上的版本。

  另一個解法，就是使用那些，可供windows 環境下，寫 unix 或 linux 環境的
  code 的軟體/系統，比方說 cygwin, msys, wsl。

  我最後是選擇在 WSL 下實作。

  另一個讓我卡一段時間的問題是在處理 suffix search 時，是要用什麼資料結
  構，因為助教提供的 suffix tree 資料結構，看起來會佔掉許多空間。

  最後是在看討論區時，有人問助教，對每一個 file 建兩個 trie，記憶體會不會不夠，
  令我想到，可參考我處理 prefix search 的方式來做處理。

  除了以上這些問題，其他就都還好，比方說要如何處理 query，如何讀取依序讀取 file，這些都只
  需要稍微動一下腦，在查些資料，就可以解決。

  四、參考資料

  https://en.cppreference.com/w/cpp/filesystem (<filesystem>的用法)

  https://stackoverflow.com/questions/54619049/compilation-errors-for-c17-
  filesystem-on-mingw (<filesystem>compile error 的原因)

  https://en.cppreference.com/w/cpp/experimental/fs/directory_iterator
  ( directory_iterator，不保證會依序輸出)

  https://stackoverflow.com/questions/21083699/segmentation-fault-core-dumped-issue-windows-to-linux
  (segment fault debug)

  https://www.geeksforgeeks.org/trie-insert-and-search/?ref=lbp
  (Trie 的資料結構&search algorithm)
