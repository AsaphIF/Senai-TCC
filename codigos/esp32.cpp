// incluindo bibliotecas

#include <string.h>
#include <ESP_Google_Sheet_Client.h>
#include <Wire.h>
#include <RTClib.h>
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

// escolha o torno exemplo: #define TORNO TORNO(1,2,3...)

#define TORNO TORNO1

// definindo o torno pela pagina e celula do GSheets

#define TORNO1 "TORNOS!D2"
#define TORNO2 "TORNOS!F2"
#define TORNO3 "TORNOS!H2"
#define TORNO4 "TORNOS!J2"
#define TORNO5 "TORNOS!L2"
#define TORNO6 "TORNOS!N2"
#define TORNO7 "TORNOS!P2"
#define TORNO8 "TORNOS!R2"

// defina o horímetro do torno ex: #define RTC_PAG RTC_(T1,T2,T3...)

#define RTC_PAG RTC_T1

// definindo horímetro do torno pela pagina e celula do GSheets

#define RTC_T1 "LADO!E3"
#define RTC_T2 "LADO!G3"
#define RTC_T3 "LADO!I3"
#define RTC_T4 "LADO!K3"
#define RTC_T5 "LADO!M3"
#define RTC_T6 "LADO!O3"
#define RTC_T7 "LADO!Q3"
#define RTC_T8 "LADO!S3"

// definindo as saidas das LEDs

#define LED_VERMELHO 2
#define LED_AMARELO 4
#define LED_VERDE 5

// definindo os wi-fis com nome e senha

#define WIFI_SSID0 "WIFI_ADM_CFP117"
#define WIFI_PASSWORD0 "CnF@Pm1!1j7@AfD3Mt"
#define WIFI_SSID1 ""     //  coloque o nome do WiFi que você quer conectar
#define WIFI_PASSWORD1 "" // coloque a senha do WiFi que você quer conectar
#define WIFI_SSID2 ""
#define WIFI_PASSWORD2 ""
#define WIFI_SSID3 ""
#define WIFI_PASSWORD3 ""

// status do wifi para debugging

#define WL_IDLE_STATUS 0
#define WL_NO_SSID_AVAIL 1
#define WL_SCAN_COMPLETED 2
#define WL_CONNECTED 3
#define WL_CONNECT_FAILED 4
#define WL_CONNECTION_LOST 5
#define WL_DISCONNECTED 6
#define WL_NO_SHIELD 255

// define variavel da rtc utilizada

RTC_DS3231 rtc;

//  coloque o "project_id" adquirido no arquivo .json em https://console.cloud.google.com/projectselector2/iam-admin/settings

#define PROJECT_ID "checklist-359119"

//  coloque o "client_email" adquirido no arquivo .json em https://console.cloud.google.com/projectselector2/iam-admin/settings

#define CLIENT_EMAIL "esp-194@checklist-359119.iam.gserviceaccount.com"

//  coloque a "private_key" adquirida no arquivo .json em https://console.cloud.google.com/projectselector2/iam-admin/settings

const char PRIVATE_KEY[] PROGMEM = "-----BEGIN PRIVATE KEY-----\nMIIEuwIBADANBgkqhkiG9w0BAQEFAASCBKUwggShAgEAAoIBAQCg6gEtTS9kjfbY\nMfG8ukeJxD2X1qQ3FwbmC7SMrY5m7ZZXvOm1xWrzb6ClF0qMBWQMstgTNfZeYpcJ\nYDuXe9+Jvxm87vja9ePed+Ao9YBFJ/e7T8Y5JB0YlqnTdbGCAthB3NUcUgqnc8dw\ngpoFdckD/rnbmDYoFR6exjPFkLoeXJszQKCjaB09lje7pmhqyfOFN1mLmT/ywmj5\nG8vLd2QSys96odCPxyiAuq6Aj7vE4gBG/bwtpnZP2yl1k1C8KH5FN5YA7a9dN/wZ\nnCXVmpWHDf3j6awQzzHyWGp+vbFZysFbvmS+j1Un0ueisV/M+RcKqVeItK11Rsfe\nAGbXanEfAgMBAAECggEAE+nxvFf9gf25qza/GmKZQNjq4HQdPX4ZifWv4esGoQFN\nJk2IRMkKO9c4M8YmoR53q8SkTfhTJYog8/WXWl9noiXmuwV+AacFjL4cHSWIusY/\n98vfFao8+ZKHsNYzYgoVFk2MiCU1EVUYPPnEsuFJP7fR63WyWhKHCBIyTQRkrCYK\nUTOpCfU+hjTbEzkoO8nTW9naChdjEeFU4SmpntD5Eo52aOO7Xdo60j8qLeEXuhx8\n7bdqLSltFhParmuRMKZuBknnXi1IduLaUQC7sqSH2Dm6JCcwfX/b21ZpEiDVuSw4\npUyc/l3S4J/YJZ1CGtNUBxKZSz/NSOkWZJ4EIzlOzQKBgQDer/OWvWpu1FcWTaLG\n0kBQUe2nt1h+ftym0fiLjUzRo4JA0hqz0sAEVG3OW9QahiQbjZcC9wyMmHsnwFAY\nkhojAuam/ZEUVOs6pgL+0WsPSNz7m8m8DA20mBcJHTTpwNXqKTjBPsqMYsiLxgfZ\nPQMTvNeh/NaA9Y8naKWPQg4/OwKBgQC4/GGYU8sRpmPQm4m3cJt3bmaQOyNhWP4F\n36jeSNkHpZKLXVJwicfZloeKJVsKZOljLdSBrIl11DHiKrxr+EKS2ig6Feqnrys2\nZpur022EOwRZm32ddPh+l9gZ+2FcY9oIX5ph/RVoJ2MPmsZ6jLI72qNYiDAItuEj\nwh8VWL4/bQKBgQCZUqYxvHsCkfrgJVYU9IBJjQ9HcaphdfFwfpNValVg5eZxwPeX\nplyE3qi382vnU0KbIfK+nOCsEPSCmxvKvxV107KBeYahbBKFz/WyAvhmjrFwH4RX\nkCkDldAOe2iKJTZjwjwMebI11HHmItQWk7aBqX0CUDZUlj4ZUSjkqQNsLwJ/LYXu\nfo4gazeHWM7uFTahC8Mfel8TVeGQoeForUtAHaGhbqqInylJBUMGF/kZbnVm+gFN\nSpwrN9QAcqgRtoBh4cHOJH1AQgPZnomhxadCTEg5ydN6FkWy4XR8uegjDZmFDop4\nc6TUn80Rk8WDEqWNNy2XBTJ+n6ZhwWsEOzyblQKBgB0ZOdaOtHehgpiss/tDH8Ta\nGQd+uMZvZi9Wou2LNy+NeGbIGpEJViSro7TZeyHdn7hu/1Lhmh2DJCoOLlJTzAGE\nj/inC+/WdMCp29UIHMcf35lvhTVRdTLgoZ9uRSRPwDAVzeQ1LNp/TSReu7MASKi5\nV6trJ1aqAiFJ5jfWivwf\n-----END PRIVATE KEY-----\n";

// coloque o "spreadsheet_id" adquirida na URL da pagina do GSheets

const char SPREADSHEET_ID[] PROGMEM = "1VtNz544ZmsqosE94fN1sAxTxm2nrxNFwwFWNmZE8SC0";

//  define a variavel para o loop

bool taskComplete = false;

//  debugging

void tokenStatusCallback(TokenInfo info);

//  metodo que encontra palavras em meio a uma frase: contem(search_range,search_key)

int contem(char str1[], char str2[])
{
    int n = 0;
    for (int i = 0; str1[i] != '\0'; i++)
    {
        int achou = 1;
        for (int j = 0; str2[j] != '\0'; j++)
        {
            if (str1[i + j] != str2[j])
            {
                achou = 0;
                break;
            }
        }
        if (achou)
        {
            n++;
        }
    }

    return n;
}

// função para conectar em um dispositivo wifi

void conectaWifi()
{

    Serial.println("Entrou no conecta wifi");

    byte numSsid = WiFi.scanNetworks();

    // mostra todos os WiFis disponiveis

    Serial.print("SSID List:");
    Serial.println(numSsid);
    for (int thisNet = 0; thisNet < numSsid; thisNet++)
    {
        Serial.print(thisNet);
        Serial.print(") Network: ");
        Serial.println(WiFi.SSID(thisNet));
    }

    // modo de procura de internet

    for (int i = 0; i < 4; i++)
    {

        digitalWrite(LED_VERMELHO, HIGH);
        delay(300);
        digitalWrite(LED_VERMELHO, LOW);
        delay(300);
        digitalWrite(LED_AMARELO, HIGH);
        delay(300);
        digitalWrite(LED_AMARELO, LOW);
        delay(300);
        digitalWrite(LED_VERDE, HIGH);
        delay(300);
        digitalWrite(LED_VERDE, LOW);
        delay(300);

        Serial.print("Tentando conectar na Internet ");
        Serial.print(i);
        Serial.print(". O status wifi é ");
        Serial.println(WiFi.status());

        if (i == 0 && WiFi.status() != WL_CONNECTED)
        {

            digitalWrite(LED_VERMELHO, HIGH);
            delay(300);
            digitalWrite(LED_VERMELHO, LOW);
            delay(300);
            digitalWrite(LED_AMARELO, HIGH);
            delay(300);
            digitalWrite(LED_AMARELO, LOW);
            delay(300);
            digitalWrite(LED_VERDE, HIGH);
            delay(300);
            digitalWrite(LED_VERDE, LOW);
            delay(300);

            WiFi.begin(WIFI_SSID0, WIFI_PASSWORD0);
            Serial.println("....tentando conectar na 1 internet....");
            delay(10000);
        }
        else if (i == 1 && WiFi.status() != WL_CONNECTED)
        {

            digitalWrite(LED_VERMELHO, HIGH);
            delay(300);
            digitalWrite(LED_VERMELHO, LOW);
            delay(300);
            digitalWrite(LED_AMARELO, HIGH);
            delay(300);
            digitalWrite(LED_AMARELO, LOW);
            delay(300);
            digitalWrite(LED_VERDE, HIGH);
            delay(300);
            digitalWrite(LED_VERDE, LOW);
            delay(300);

            WiFi.begin(WIFI_SSID1, WIFI_PASSWORD1);
            Serial.println("....tentando conectar na 2 internet....");
            delay(10000);
        }
        else if (i == 2 && WiFi.status() != WL_CONNECTED)
        {
            digitalWrite(LED_VERMELHO, HIGH);
            delay(300);
            digitalWrite(LED_VERMELHO, LOW);
            delay(300);
            digitalWrite(LED_AMARELO, HIGH);
            delay(300);
            digitalWrite(LED_AMARELO, LOW);
            delay(300);
            digitalWrite(LED_VERDE, HIGH);
            delay(300);
            digitalWrite(LED_VERDE, LOW);
            delay(300);

            WiFi.begin(WIFI_SSID2, WIFI_PASSWORD2);
            Serial.println("....tentando conectar na 3 internet....");
            delay(10000);
        }
        else if (i == 3 && WiFi.status() != WL_CONNECTED)
        {

            digitalWrite(LED_VERMELHO, HIGH);
            delay(300);
            digitalWrite(LED_VERMELHO, LOW);
            delay(300);
            digitalWrite(LED_AMARELO, HIGH);
            delay(300);
            digitalWrite(LED_AMARELO, LOW);
            delay(300);
            digitalWrite(LED_VERDE, HIGH);
            delay(300);
            digitalWrite(LED_VERDE, LOW);
            delay(300);

            WiFi.begin(WIFI_SSID3, WIFI_PASSWORD3);
            Serial.println("....tentando conectar na 4 internet....");
            delay(10000);
        }

        digitalWrite(LED_VERMELHO, HIGH);
        digitalWrite(LED_AMARELO, HIGH);
        digitalWrite(LED_VERDE, HIGH);
        delay(300);
        digitalWrite(LED_VERMELHO, LOW);
        digitalWrite(LED_AMARELO, LOW);
        digitalWrite(LED_VERDE, LOW);
        delay(300);
        digitalWrite(LED_VERMELHO, HIGH);
        digitalWrite(LED_AMARELO, HIGH);
        digitalWrite(LED_VERDE, HIGH);
        delay(300);
        digitalWrite(LED_VERMELHO, LOW);
        digitalWrite(LED_AMARELO, LOW);
        digitalWrite(LED_VERDE, LOW);
        delay(300);
    }
}

// Função para verificar o estado da conexão e conectar caso esteja desconectado

void verificaWifi()
{
    Serial.print("Verifica sinal... Status: ");
    Serial.println(WiFi.status());

    while (WiFi.status() != WL_CONNECTED)
    {
        conectaWifi();
    }
}

//  definindo GPIOs e RTC

void setup()
{
    pinMode(18, INPUT);
    pinMode(LED_VERMELHO, OUTPUT);
    pinMode(LED_AMARELO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);

    Serial.begin(115200);

    //  só inicia a ESP32 se o RTC estiver conectado

    if (!rtc.begin())
    {
        Serial.println("Não encontrou o RTC");
        Serial.flush();
        while (1)
            delay(10);
    }
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    if (rtc.lostPower())
    {
        Serial.println("RTC desligou, definindo horário!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    Serial.println();
    Serial.println();
    Serial.print("Conectando ao Wi-Fi");

    conectaWifi();

    //  só para debugging do GSheets

    GSheet.setTokenCallback(tokenStatusCallback);
    GSheet.begin(CLIENT_EMAIL, PROJECT_ID, PRIVATE_KEY);
}

// começando o programa

void loop()
{
    Serial.println("------------------ Início do Loop() ----------------------------");

    // fica autenticando a conexão com o GSheets

    bool ready = GSheet.ready();

    // se conectou ao GSheets e o loop estiver ativo ele inicia os comandos

    if (ready && !taskComplete)
    {

        //  data e hora de hoje

        DateTime now = rtc.now();

        //  formato de hora:minuto

        char buf1[] = "hh:mm";
        Serial.println(now.toString(buf1));

        // formato de dia mes ano - hora minuto segundo

        char buf2[] = "DDMMYY-hh:mm:ss";
        Serial.println(now.toString(buf2));

        // formato de diaSemana , dia mes ano

        char buf3[] = "Hoje é DDD, DD MMM YYYY";
        Serial.println(now.toString(buf3));

        // formato de dia mes ano

        char buf4[] = "DD-MM-YYYY";
        Serial.println(now.toString(buf4));

        //  formatação em FirebaseJson

        FirebaseJson response;
        FirebaseJson valueRange;

        // comunicação com GSheets (Escrita de Celula - RTC)

        valueRange.add("majorDimension", "COLUMNS");
        valueRange.set("values/[0]/[0]", buf1);
        bool successa;

        // se a entrada 18 for HIGH então a RTC vai enviar dados ao GSheets

        if (digitalRead(18) == HIGH)
        {

            successa = GSheet.values.append(&response, SPREADSHEET_ID, RTC_T1, &valueRange);
            response.toString(Serial, true);
            Serial.println();
        }

        // comunicação com o GSheets (Leitura de Celula)

        Serial.println("\n Pegando o valor da celula...");
        Serial.println("---------------------------------------------------------------");

        bool success;
        success = GSheet.values.get(&response, SPREADSHEET_ID, TORNO);
        Serial.println();

        FirebaseJsonData valores;
        String resultado;

        //  pega valores lidos

        response.get(valores, "values");

        //  se conseguir ler o valor transforma o os valores lidos em string

        if (valores.success)
        {
            Serial.println("deu");
            resultado = valores.to<String>();
        }
        else
            Serial.println("não deu");

        // criando conjunto de chars com tamanho da string

        char stats[resultado.length() + 1];

        // copia os valores da string no char

        strcpy(stats, resultado.c_str());

        //  variaveis para comparar

        char amarelo[] = {"AMARELO"};
        char verde[] = {"VERDE"};
        char vermelho[] = {"VERMELHO"};
        char desligado[] = {"DESLIGADO"};

        //  resultado

        int temR = contem(stats, vermelho);
        int temY = contem(stats, amarelo);
        int temG = contem(stats, verde);
        int ntem = contem(stats, desligado);

        // condições para cada estado

        if (temR != 0)
        {
            //  se o estado for VERMELHO então o LED VERMELHO vai ligar intermitentemente

            Serial.println("LED VERMELHO");
            digitalWrite(LED_VERMELHO, LOW);
            digitalWrite(LED_AMARELO, LOW);
            digitalWrite(LED_VERDE, LOW);
            delay(1000);

            digitalWrite(LED_VERMELHO, HIGH);
            digitalWrite(LED_AMARELO, LOW);
            digitalWrite(LED_VERDE, LOW);
        }
        if (temY != 0)
        {
            //  se o estado for AMARELO então o LED AMARELO vai ligar

            Serial.println("LED AMARELO");
            digitalWrite(LED_AMARELO, HIGH);
            digitalWrite(LED_VERMELHO, LOW);
            digitalWrite(LED_VERDE, LOW);
        }
        if (temG != 0)
        {
            //  se o estado for VERDE então o LED VERDE vai ligar

            Serial.println("LED VERDE");
            digitalWrite(LED_VERDE, HIGH);
            digitalWrite(LED_VERMELHO, LOW);
            digitalWrite(LED_AMARELO, LOW);
        }
        if (ntem != 0)
        {
            //  se o estado for DESLIGADO então o LED VERMELHO vai ligar

            digitalWrite(LED_VERDE, LOW);
            digitalWrite(LED_VERMELHO, HIGH);
            digitalWrite(LED_AMARELO, LOW);
        }
        else
        {
            // erro na hora da passagem de dados

            Serial.println("Nenhum dado encontrado!");
        }

        // se "false" o loop continua; se "true" o loop acontece só uma vez

        taskComplete = false;
    }

    //  Verifica a conexão com o wifi

    verificaWifi();

    Serial.println("------------------ Fim do Loop() ----------------------------");
}

// debugging do GSheets

void tokenStatusCallback(TokenInfo info)
{
    if (info.status == esp_signer_token_status_error)
    {
        Serial.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
        Serial.printf("Token error: %s\n", GSheet.getTokenError(info).c_str());
    }
    else
    {
        Serial.printf("Token info: type = %s, status = %s\n", GSheet.getTokenType(info).c_str(), GSheet.getTokenStatus(info).c_str());
    }
}