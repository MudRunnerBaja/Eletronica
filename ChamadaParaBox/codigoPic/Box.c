char output[255];
void boxHandler(char ans);

void main() {
  UART1_Init(9600);
  Delay_ms(100);
  TRISD.F0 = 0;

  while (1) {
    if (UART_Data_Ready() == 1) {
      UART_Read_Text(output, "\n", 255);
      boxHandler(output);
    }
  }
}

void boxHandler(char ans) {
  char *res = strstr(ans, "K2PQ"); // Comparar strings
  if (res) {
    LATD.F0 = 1;
  }
}