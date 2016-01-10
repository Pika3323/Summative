#include "Online.h"

LevelVotes Online::v = { 0, 0 };
int Online::completions = 0;
int Online::attempts = 0;
bool Online::bVerbose = true;

void Online::PostLevel(const char* LevelName){
	char level[64];
	strcpy(level, LevelName);

	strcat(level, ".bvl");

	FILE* fd;

	fd = fopen(level, "rb");
	if (!fd){
		fprintf(stderr, "Could not open %s\n", level);
		return;
	}
	fseek(fd, 0L, SEEK_END);
	int sz = ftell(fd);
	fseek(fd, 0L, SEEK_SET);

	CURL *curl;
	CURLcode res;

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect:";

	curl_global_init(CURL_GLOBAL_ALL);

	/* Fill in the file upload field */
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "levelfile",
		CURLFORM_FILE, level,
		CURLFORM_END);

	/* Fill in the filename field */
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "username",
		CURLFORM_COPYCONTENTS, "TestUser",
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "levelname",
		CURLFORM_COPYCONTENTS, LevelName,
		CURLFORM_END);


	/* Fill in the submit field too, even if this is rarely needed */
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "submit",
		CURLFORM_COPYCONTENTS, "send",
		CURLFORM_END);

	curl = curl_easy_init();
	/* initialize custom header list (stating that Expect: 100-continue is not
	wanted */
	headerlist = curl_slist_append(headerlist, buf);
	if (curl) {
		if (bVerbose){
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		curl_easy_setopt(curl, CURLOPT_URL, "http://blocks.llamabagel.ca/PostNewLevel");

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		//always cleanup
		curl_easy_cleanup(curl);

		//then cleanup the formpost chain
		curl_formfree(formpost);
		//free slist 
		curl_slist_free_all(headerlist);
	}
}

void Online::UpdateLevel(const char* LevelName, int id, LevelData data){
	char level[64];
	strcpy(level, LevelName);

	strcat(level, ".bvl");

	CURL *curl;
	CURLcode res;

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect:";

	curl_global_init(CURL_GLOBAL_ALL);

	switch (data){
	case File:
		/* Fill in the file upload field */
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "levelfile",
			CURLFORM_FILE, level,
			CURLFORM_END);
		break;
	case Completions:
		char sCom[5];
		_itoa(completions, sCom, 10);
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "levelcompletions",
			CURLFORM_COPYCONTENTS, sCom,
			CURLFORM_END);
		break;
	case Tries:
		char sTries[5];
		_itoa(attempts, sTries, 10);
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "leveltries",
			CURLFORM_COPYCONTENTS, sTries,
			CURLFORM_END);
		break;
	case Votes:
		char sUp[5];
		_itoa(v.up, sUp, 10);
		char sDown[5];
		_itoa(v.down, sDown, 10);
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "levelupvotes",
			CURLFORM_COPYCONTENTS, sUp,
			CURLFORM_END);
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "leveldownvotes",
			CURLFORM_COPYCONTENTS, sDown,
			CURLFORM_END);
		break;
	}
	char sType[2];
	_itoa(data, sType, 10);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "updatetype",
		CURLFORM_COPYCONTENTS, sType,
		CURLFORM_END);
	char sID[5];
	_itoa(id, sID, 10);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "levelid",
		CURLFORM_COPYCONTENTS, sID,
		CURLFORM_END);

	/* Fill in the filename field */
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "username",
		CURLFORM_COPYCONTENTS, "TestUser",
		CURLFORM_END);

	/* Fill in the submit field too, even if this is rarely needed */
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "submit",
		CURLFORM_COPYCONTENTS, "send",
		CURLFORM_END);

	curl = curl_easy_init();
	/* initialize custom header list (stating that Expect: 100-continue is not
	wanted */
	headerlist = curl_slist_append(headerlist, buf);
	if (curl) {
		if (bVerbose){
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		curl_easy_setopt(curl, CURLOPT_URL, "http://blocks.llamabagel.ca/UpdateLevel");

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		//always cleanup
		curl_easy_cleanup(curl);

		//then cleanup the formpost chain
		curl_formfree(formpost);
		//free slist 
		curl_slist_free_all(headerlist);
	}
}

void Online::DeleteLevel(int id){
	char sID[5];
	_itoa(id, sID, 10);

	struct MemoryStruct chunk;

	chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	CURL *curl;
	CURLcode res;

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect:";

	curl_global_init(CURL_GLOBAL_ALL);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "levelid",
		CURLFORM_COPYCONTENTS, sID,
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "submit",
		CURLFORM_COPYCONTENTS, "send",
		CURLFORM_END);

	curl = curl_easy_init();
	/* initialize custom header list (stating that Expect: 100-continue is not
	wanted */
	headerlist = curl_slist_append(headerlist, buf);
	if (curl) {
		if (bVerbose){
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		curl_easy_setopt(curl, CURLOPT_URL, "http://blocks.llamabagel.ca/DeleteLevel");

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		printf("%lu bytes retrieved\n", (long)chunk.size);
		printf("%s\n", chunk.memory);

		//always cleanup
		curl_easy_cleanup(curl);

		//then cleanup the formpost chain

		free(chunk.memory);

		curl_formfree(formpost);
		//free slist 
		curl_slist_free_all(headerlist);
	}
}

void Online::GetLevelData(const char* username, std::vector<WorldLevelData> &V){
	std::vector<WorldLevelData> Levels;

	struct MemoryStruct chunk;

	chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	CURL *curl;
	CURLcode res;

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect:";

	curl_global_init(CURL_GLOBAL_ALL);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "username",
		CURLFORM_COPYCONTENTS, username,
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "submit",
		CURLFORM_COPYCONTENTS, "send",
		CURLFORM_END);

	curl = curl_easy_init();
	/* initialize custom header list (stating that Expect: 100-continue is not
	wanted */
	headerlist = curl_slist_append(headerlist, buf);
	if (curl) {
		if (bVerbose){
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		curl_easy_setopt(curl, CURLOPT_URL, "http://blocks.llamabagel.ca/GetUserLevels");

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		FILE *tmp = NULL;

		tmp = fopen("temp.temp", "w");
		fflush(stdin);
		fputs(chunk.memory, tmp);

		fclose(tmp);

		fopen("temp.temp", "r");
		int c, lines = 0;


		while ((c = fgetc(tmp)) != EOF) {
			if (c == '\n')
				lines++;
		}
		rewind(tmp);
		for (int i = 0; i < lines; i++){
			int id;
			char * Name;
			char * User;
			char * Date;
			int Attempts, Completions, Upvotes, Downvotes;
			char line[256];
			char * sTemp;

			//Gets a single line from the temporary file which represents a single level
			fgets(line, 256, tmp);

			//Get the ID of the level
			sTemp = strtok(line, ",");
			sscanf(sTemp, "%d", &id);

			//Get the name of the level
			Name = strtok(NULL, ",");

			//Get the username of the creator
			User = strtok(NULL, ",");

			//Get the timestamp of upload
			Date = strtok(NULL, ",");

			//Get the number of attempts
			sTemp = strtok(NULL, ",");
			sscanf(sTemp, "%d", &Attempts);

			//Get the number of completions
			sTemp = strtok(NULL, ",");
			sscanf(sTemp, "%d", &Completions);

			//Get the number of upvotes
			sTemp = strtok(NULL, ",");
			sscanf(sTemp, "%d", &Upvotes);

			//Get the number of downvotes
			sTemp = strtok(NULL, ",");
			sscanf(sTemp, "%d", &Downvotes);

			Levels.push_back(WorldLevelData(id, Name, User, Date, Attempts, Completions, Upvotes, Downvotes));
		}

		//always cleanup
		curl_easy_cleanup(curl);

		//then cleanup the formpost chain

		free(chunk.memory);

		//then cleanup the formpost chain

		curl_formfree(formpost);
		//free slist 
		curl_slist_free_all(headerlist);

	}
	V = Levels;
}

WorldLevelData Online::GetLevelData(int LevelID){
	int id;
	char * Name;
	char * User;
	char * Date;
	int Attempts, Completions, Upvotes, Downvotes;
	char line[256];
	char * sTemp;

	struct MemoryStruct chunk;

	chunk.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
	chunk.size = 0;    /* no data at this point */

	CURL *curl;
	CURLcode res;

	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	static const char buf[] = "Expect:";

	curl_global_init(CURL_GLOBAL_ALL);

	char sID[5];
	_itoa(LevelID, sID, 10);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "levelid",
		CURLFORM_COPYCONTENTS, sID,
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "submit",
		CURLFORM_COPYCONTENTS, "send",
		CURLFORM_END);

	curl = curl_easy_init();
	/* initialize custom header list (stating that Expect: 100-continue is not
	wanted */
	headerlist = curl_slist_append(headerlist, buf);
	if (curl) {
		if (bVerbose){
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

		curl_easy_setopt(curl, CURLOPT_URL, "http://blocks.llamabagel.ca/GetIDLevel");

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));

		FILE *tmp = NULL;

		tmp = fopen("temp.temp", "w");
		fflush(stdin);
		fputs(chunk.memory, tmp);

		fclose(tmp);

		fopen("temp.temp", "r");

		//Gets a single line from the temporary file which represents a single level
		fgets(line, 256, tmp);

		//Get the ID of the level
		sTemp = strtok(line, ",");
		sscanf(sTemp, "%d", &id);

		//Get the name of the level
		Name = strtok(NULL, ",");

		//Get the username of the creator
		User = strtok(NULL, ",");

		//Get the timestamp of upload
		Date = strtok(NULL, ",");

		//Get the number of attempts
		sTemp = strtok(NULL, ",");
		sscanf(sTemp, "%d", &Attempts);

		//Get the number of completions
		sTemp = strtok(NULL, ",");
		sscanf(sTemp, "%d", &Completions);

		//Get the number of upvotes
		sTemp = strtok(NULL, ",");
		sscanf(sTemp, "%d", &Upvotes);

		//Get the number of downvotes
		sTemp = strtok(NULL, ",");
		sscanf(sTemp, "%d", &Downvotes);

		//always cleanup
		curl_easy_cleanup(curl);

		//then cleanup the formpost chain

		free(chunk.memory);

		//then cleanup the formpost chain

		curl_formfree(formpost);
		//free slist 
		curl_slist_free_all(headerlist);

	}
	return WorldLevelData(id, Name, User, Date, Attempts, Completions, Upvotes, Downvotes);
}

void Online::GetLevel(int LevelID){
	WorldLevelData W = GetLevelData(LevelID);

	FILE* Level;

	char sID[5];
	_itoa(LevelID, sID, 10);

	char save[32] = "Levels/";
	char get[64] = "http://blocks.llamabagel.ca/Levels/Files/";

	strcat(get, sID);
	strcat(get, ".bvl");

	strcat(save, W.Name);
	strcat(save, ".bvl");

	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl) {
		Level = fopen(save, "wb");

		if (bVerbose){
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		}

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_save);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, Level);

		curl_easy_setopt(curl, CURLOPT_URL, get);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		fclose(Level);
		//always cleanup
		curl_easy_cleanup(curl);

	}
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

static size_t write_save(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}