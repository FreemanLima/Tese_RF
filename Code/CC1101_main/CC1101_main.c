#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "pico/cyw43_arch.h"

#include "Registers.h" //lista dos registos e afins


/*
#include "blink.pio.h"

void blink_pin_forever(PIO pio, uint sm, uint offset, uint pin, uint freq) {
    blink_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);

    printf("Blinking pin %d at %d Hz\n", pin, freq);

    // PIO counter program takes 3 more cycles in total than we pass as
    // input (wait for n + 1; mov; jmp)
    pio->txf[sm] = (125000000 / (2 * freq)) - 3;
}
*/
/*
int64_t alarm_callback(alarm_id_t id, void *user_data) {
    // Put your timeout handler code in here
    return 0;
}
*/

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

void SPI_init() {
    // SPI initialisation. This example will use SPI at 1MHz.
    spi_init(SPI_PORT, 1000*1000);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_CS,   GPIO_FUNC_SIO);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
}

uint8_t WIFI_On = 0;
uint8_t wifi_innit() {
    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return 0;
    }
    return 1;
}


// O sistema vai ter 2 modos principais, 433MHz e 868Mhz, dentro destes modos podemos ter RX e TX.
// A escolha da frequência é feita por dois RF_SW's, 
//2 pins para controlar, GPIOX e GPIOY
//se freq_select = 0, 433Mhz, se freq_select = 1, 868Mhz 
//GPIOX = freq_select, GPIOY = !freq_select  isto pq por razoes de layout as frequencias estao trocadas nos switches, consultar esquematica para confirmar se houver duvidas

/* Key Parameters to set in the CC1101: (from datasheet pagina 27)
        Power-down / power up mode
        Crystal oscillator power-up / power-down
        Receive / transmit mode
        RF channel selection
        Data rate
        Modulation format
        RX channel filter bandwidth
        RF output power
        Data buffering with separate 64-byte
        receive and transmit FIFOs
        Packet radio hardware support
        Forward Error Correction (FEC) with
        interleaving
        Data whitening
        Wake-On-Radio (WOR)
*/

//sempre q mandamos algo no SPI temos de meter CS low, mas é possivel q ja seja feito automaticamente pelo pico usando as funcoes
// formato geral do header byte, R/W 1-Read, 0-Write, BURST, ADDR 6bits, 
// depois é um byte de dados, se for para escrever ou ler 1 byte do SO se for para ler

//depois de mandar um header, um data byte ou um burst o chip manda ao mesmo tempo um byte de status que deve ser lido e tratado (pagina 31 tabela 23)

// o burst bit basicamente serve como uma maneira facil de escrever e ler registos consecutivos, se for 1 vai incrementando a partir do primeiro endereco até o CS for a High, mas dos enderecos 0x30 até 0x3D, o burst bit tem outro comportamento, ler pagina 32


//pagina 33 tem a explicacao de como usar os registos de RX e TX de maneira simples

//pagina 33 tem tambem a explicacao da PATABLE que é as configuracoes do output power e ASK modulation shaping

//DATA Rate programming - pag.35
//Receiver Channel Filter Bandwidth Programming - pag.35


//usar isto para comunicar ISP
//int spi_write_read_blocking(spi_inst_t *spi, const uint8_t *src, uint8_t *dst, size_t len);
int main()
{
    stdio_init_all();
    SPI_init();
    WIFI_On = wifi_innit();
    //add_alarm_in_ms(2000, alarm_callback, NULL, false);


    
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}





    // For more examples of timer use see https://github.com/raspberrypi/pico-examples/tree/master/timer

    /*
    // Enable wifi station
    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms("Your Wi-Fi SSID", "Your Wi-Fi Password", CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("failed to connect.\n");
        return 1;
    } else {
        printf("Connected.\n");
        // Read the ip address in a human readable way
        uint8_t *ip_address = (uint8_t*)&(cyw43_state.netif[0].ip_addr.addr);
        printf("IP address %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
    }

    */


        // For more examples of SPI use see https://github.com/raspberrypi/pico-examples/tree/master/spi
    // For more pio examples see https://github.com/raspberrypi/pico-examples/tree/master/pio

    // Timer example code - This example fires off the callback after 2000ms