# Trie

## Description

A simple Trie data structure for efficiently storing text. Can easily be extended to support templates for data stored in addition to identifying key.  

For instance, a set of definitions at the last character of each word.

## Features

- `void addWord(string)`  
-- inserts word into the trie  

- `bool wordExists(string)`  
-- check if a word exists in the trie

- `vector<string> matchPartial(string)`  
-- find all words that match the input substr from the start