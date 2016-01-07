#include "Online.h"

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
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		/* what URL that receives this POST */

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

void Online::UpdateLevel(const char* LevelName, int id, LevelData data, const void* change){
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
		curl_formadd(&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "levelcompletions",
			CURLFORM_COPYCONTENTS, (int)*change,
			CURLFORM_END);
		break;
	case Tries:
		break;
	case Votes:
		break;
	}
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "updatetype",
		CURLFORM_COPYCONTENTS, data,
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
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		/* what URL that receives this POST */

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