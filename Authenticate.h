#pragma once
#include "gui.h"
#include "VMProtectSDK.h"
#include "AES256.hpp"
#include "base64.h"
#include "misc.h"
#include "xorstring.h"
#include "xorstring.h"

bool cantaccess = false;
bool loadedscr = false;

bool is_original = false;
bool is_lite = false;
bool is_extended = false;

/*
[#] Made by: GGScript4FE, NovsX & AeroCat/David.
[#] Made for: Nova
*/
#pragma comment (lib, "curl/libcurl_a_debug.lib")

DWORD authorize(const std::string &username, const std::string &password) {
	VMProtectBeginUltra("Nova authentication");

	/* compile time string encryption, makes these strings invisible to decompilers */
	XorS(A, "https://PyramidAuthentication.org");
	XorS(B, "/authentication/authversion.php?version=1.2.1&info=");
	XorS(C, "1jeufieo39cjduejsu38do9023ut0923");
	XorS(D, "/authentication/version.php");
	XorS(E, "/authentication///information.php");
	XorS(N, "/authentication/classified.php");
	XorS(P, "REZ61ZkrqeX2DqNBK207I1X2GcN");
	XorS(F, "You are currently (temporarily) banned from using Nova! Please check back later");
	XorS(H, "Username or password was invalid");
	XorS(J, "Welcome and thank you for purchasing Nova! This authentication time is going to take longer than usual.");
	XorS(L, " Authentication Failed!");
	XorS(M, "Authentication Failed");
	XorS(R, "Nova rewrite");
	XorS(S, "There is an issue with your internet connection. Please fix the issue then try again.");
	XorS(T, "!kxK4Vsvl_dnB3q0ZhQazdg");

	srand(time(NULL));

	std::string random;

	for (int i = 0; i < 16; i++)
		random += (char)(rand() % 256); //It just generates a random key.

	/* definitions */

	std::string key = C.decrypt(); //decrypt key
	std::string host = A.decrypt();
	std::string roblox_versionhost = "http://setup.roblox.com/version"; /* Everyone knows wot this is! If you don't then you are a retard.. */

	std::string hwidhere = get_hwid();
	std::string path = B.decrypt() + urlencode(base64_encode(AES256_Encrypt(hwidhere + char(0) + username + char(0) + password + char(0) + random, key)));
	std::string verpath = D.decrypt();
	std::string otherpath = E.decrypt();
	std::string trialpath = N.decrypt();

	std::string banned_response = "A17AWr9JtAa8MLciWHPy"; //The banned boolean.
	std::string invalidhwid_response = "DN23fj2iopj3hrf09823"; //if the hwid is invalid
	std::string firsttime_response = "h97grf38qh98egh08i"; //if this is a first time launch
	std::string changelog_response = "SDF34324JD9FG902DFSOP"; //response if first time running *this* version
	std::string trial_response = P.decrypt(); //response for trial. Do not delete. It is important for every exploit!

	std::string wlurl = host + path;
	std::string verurl = host + verpath;
	std::string otherurl = host + otherpath;
	std::string trialurl = host + trialpath;
	std::string content = download_url(wlurl);
	std::string online_version = download_url(verurl);
	std::string decrypted = AES256_Decrypt(base64_decode(content), key);

	std::vector<std::string> alldata = split_string(decrypted, ':');
	std::string membership_type = alldata[0];


	if (content == banned_response) /* If you are banned this will happen!*/
	{
		MessageBox(NULL, F.decrypt(), R.decrypt(), MB_ICONERROR | MB_OK);

		EnableWindow(password_field, true);
		EnableWindow(username_field, true);
		EnableWindow(submit, true);
		return 0;
	}

	if (content == invalidhwid_response) //if HWID was invalid, but other information was valid, the difference here is the "!" at the end of the title
	{
		MessageBox(NULL, H.decrypt(), L.decrypt(), MB_ICONERROR | MB_OK);

		EnableWindow(password_field, true);
		EnableWindow(username_field, true);
		EnableWindow(submit, true);
		return 0;
	}

	if (content == firsttime_response) /* The first time you use Nova ;-; */
	{
		MessageBox(NULL, J.decrypt(), R.decrypt(), MB_ICONINFORMATION | MB_OK);
		auth_firsttime = true;
		authorize(username, password);
		return 0;
	}

	if (content == changelog_response)
	{
		std::string changelog = "Changelog here!";

		MessageBox(NULL, changelog.c_str(), R.decrypt(), MB_ICONINFORMATION | MB_OK);
		authorize(username, password);
		return 0;
	}

	if (membership_type == "Main")
	{
		is_original = true;
	}

	if (membership_type == "Tryout")
	{
		is_lite = true;
	}

	if (membership_type == "V.I.P TRYOUT")
	{
		is_extended = true;
	}

	if (alldata[1] != random)
	{
		if (download_url("/*Pastebin link\*") != "connected") {
			MessageBox(NULL, S.decrypt(), R.decrypt(), MB_ICONINFORMATION | MB_OK);

			EnableWindow(password_field, true);
			EnableWindow(username_field, true);
			EnableWindow(submit, true);
			return 0;
		}

		MessageBox(NULL, H.decrypt(), M.decrypt(), MB_ICONERROR | MB_OK);

		EnableWindow(password_field, true);
		EnableWindow(username_field, true);
		EnableWindow(submit, true);
	}

	else {
		if (online_version != SW_VERSION) {
			std::string msgbox_str = "Nova new update has been published: " + online_version + "\r\nPress 'YES' to go to the download link.\n(Mega.nz key copied to your clipboard!)";

			if (MessageBox(NULL, msgbox_str.c_str(), R.decrypt(), MB_ICONINFORMATION | MB_YESNO) == IDYES) {
				system("start */link for download\*");
				to_clipboard(NULL, T.decrypt());
			}

			EnableWindow(password_field, true);
			EnableWindow(username_field, true);
			EnableWindow(submit, true);
		}

		else {
			if (download_url(roblox_versionhost) != SW_CLIENTVERSION) {
				if (MessageBox(NULL, "It seems like RobloxPlayerBeta was updated. Do you want to continue after all?", R.decrypt(), MB_ICONWARNING | MB_YESNO) == IDNO)
					ExitThread(0);
			}

			auth_success = true;
		}
	}

	VMProtectEnd();
}

void init_auth() {
	EnableWindow(password_field, false);
	EnableWindow(username_field, false);
	EnableWindow(submit, false);

	int p_length = GetWindowTextLength(password_field) + 1;
	GetWindowText(password_field, (LPSTR)pass_buffer, p_length);

	int u_length = GetWindowTextLength(username_field) + 1;
	GetWindowText(username_field, (LPSTR)user_buffer, u_length);

	authorize(user_buffer, pass_buffer);
}

/* validate the folder that holds the username and encoded password */
void check_authfolder()
{
	struct stat info;

	auto pathname = (char*)"C:\\SW_AUTH";

	if (stat(pathname, &info) != 0)
	{
		cantaccess = true;
	}

	else if (info.st_mode & S_IFDIR)
	{
		loadedscr = true;
	}

	if (cantaccess)
	{
		CreateDirectory(pathname, NULL);

		if (!loadedscr)
			MessageBox(NULL, "There was an errror finding the password and username from its location :(", "Nova rewrite", MB_ICONERROR | MB_OK);
	}
}
