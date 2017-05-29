#include <cstdio>
#include <cstring>
#include <cassert>
#include <string>
#include <map>
#include <vector>

static std::map<char, int> letter_to_key
{
	{ 'i', 1 }, { 'j', 1 },
	{ 'a', 2 }, { 'b', 2 }, { 'c', 2 },
	{ 'd', 3 }, { 'e', 3 }, { 'f', 3 },
	{ 'g', 4 }, { 'h', 4 },
	{ 'k', 5 }, { 'l', 5 },
	{ 'm', 6 }, { 'n', 6 },
	{ 'p', 7 }, { 'r', 7 }, { 's', 7 },
	{ 't', 8 }, { 'u', 8 }, { 'v', 8 },
	{ 'w', 9 }, { 'x', 9 }, { 'y', 9 },
	{ 'o', 0 }, { 'q', 0 }, { 'z', 0 },
};

struct trie
{
	void insert_word(const char *str);

	struct node
	{
		~node();
	
		char *word = 0;
		node *children[10] {};
	};

	node root;
};

void
trie::insert_word(const char *str)
{
	node *cur_node = &root;

	for (const char *p = str; *p; p++) {
		auto it = letter_to_key.find(*p);
		assert(it != letter_to_key.end());

		int child = it->second;

		if (!cur_node->children[child])
			cur_node->children[child] = new node;

		cur_node = cur_node->children[child];
	}

	cur_node->word = new char[strlen(str) + 1];
	strcpy(cur_node->word, str);
}

trie::node::~node()
{
	delete[] word;

	for (int i = 0; i < 10; i++)
		delete children[i];
}

static void
solve(const trie& trie, const char *str)
{
	int len = strlen(str);

	std::vector<std::pair<int, const char *> > partial(len);

	for (int i = len - 1; i >= 0; i--) {
		partial[i] = std::make_pair<int, const char *>(0, 0);

		const trie::node *cur_node = &trie.root;

		for (const char *p = &str[i]; *p; p++) {
			assert(*p >= '0' && *p <= '9');

			if (!(cur_node = cur_node->children[*p - '0']))
				break;

			if (cur_node->word) {
				int wlen = p - &str[i] + 1;

				if (p[1] == '\0' || partial[i + wlen].second) {
					int count = p[1] == '\0' ? 1 : 1 + partial[i + wlen].first;

					if (partial[i].first == 0 || partial[i].first > count) {
						partial[i].first = count;
						partial[i].second = cur_node->word;
					}
				}
			}
		}
	}

	if (partial[0].first == 0) {
		printf("No solution.\n");
	} else {
		int i = 0;

		while (i < len) {
			printf("%s ", partial[i].second);
			i += strlen(partial[i].second);
		}

		putchar('\n');
	}
}

int
main()
{
	char numbers[512];

	while (scanf("%s\n", numbers) == 1 && strcmp(numbers, "-1")) {
		trie trie;

		int nwords;

		scanf("%d\n", &nwords);

		for (int i = 0; i < nwords; i++) {
			char word[512];
			scanf("%s\n", word);
			trie.insert_word(word);
		}

		solve(trie, numbers);
	}
}