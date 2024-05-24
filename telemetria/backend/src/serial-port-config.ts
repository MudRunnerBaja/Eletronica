export class SerialPortConfiguration {
  public path: string;
  public baudRate: number;
  public dataBits: number;
  public stopBits: number;
  public parity: string;
}

export const DEFAULT_SERIAL_PORT_CONFIGURATION: SerialPortConfiguration = 
{
  "path": "COM6",
  "baudRate": 9600,
  "dataBits": 8,
  "stopBits": 1,
  "parity": "none"
}
