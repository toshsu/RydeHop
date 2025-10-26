// Helper function to recursively collect suggestions
static void collect_suggestions(TrieNode *node, char *buffer, int depth, void (*callback)(char*, void*)) {
    if (node == NULL) return;

    if (node->is_end_of_word) {
        buffer[depth] = '\0';
        callback(buffer, node->data);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            buffer[depth] = 'a' + i;
            collect_suggestions(node->children[i], buffer, depth + 1, callback);
        }
    }
}

// Autocomplete suggestions based on prefix
void trie_autocomplete(Trie *trie, const char *prefix, void (*callback)(char*, void*)) {
    TrieNode *current = trie->root;
    int len = strlen(prefix);

    for (int i = 0; i < len; i++) {
        char ch = tolower(prefix[i]);
        if (ch < 'a' || ch > 'z')
            continue;

        int index = ch - 'a';
        if (!current->children[index])
            return; // No suggestions found

        current = current->children[index];
    }

    char buffer[100];
    strcpy(buffer, prefix);
    collect_suggestions(current, buffer, strlen(prefix), callback);

}
