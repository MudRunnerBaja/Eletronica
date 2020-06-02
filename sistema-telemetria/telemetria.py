import PySimpleGUI as sg
import serial
from openpyxl import Workbook

wb = Workbook()

#Variaveis globais:
carro = {"Velocidade":"","RPM":"","Latitude":"","Longitude":"","Temperatura":""}
line = 2
conexao = False
teste = 1
vel = 0

def ExcelInit(test = teste):
	global planilha
	global teste
	global wb
	global planilha
	global line
	
	if teste == 1:
		planilha = wb.active
		planilha.title = "Teste1"
	else:
		planilha = wb.create_sheet()
		planilha.title = f"Teste{teste}"
		line = 2
		
	planilha['A1'] = "Velocidade"
	planilha['B1'] = "RPM"
	planilha['C1'] = "Latitude"
	planilha['D1'] = "Longitude"
	planilha['E1'] = "Temperatura"
	
def SalvarDados():
	global carro
	global line
	global planilha
	global wb
	planilha[f'A{line}'] = carro["Velocidade"]
	planilha[f'B{line}'] = carro["RPM"]
	planilha[f'C{line}'] = carro["Latitude"]
	planilha[f'D{line}'] = carro["Longitude"]
	planilha[f'E{line}'] = carro["Temperatura"]
	line = line + 1
	wb.save(f"AceRet.xlsx")
		
def RecebeDados():
	global carro
	recebedados = True
	while recebedados is True:
		try:
			string = ser.readline().decode("ascii")
			lista = string.split(":")
			carro[lista[0]] = lista[1]
			if lista[0] == "Temperatura":
				SalvarDados() 
				recebedados = False
				
		except Exception as e:
			print(e)
	print("Dados foram salvados")	

def AtualizaValor():
	janela_principal['velocidade'].update(carro['Velocidade'])
	janela_principal['rpm'].update(carro['RPM'])
	janela_principal['temperatura'].update(carro['Temperatura'])
	

layout_vel = [
	[sg.Text("00",key="velocidade",font=(None,100)),sg.Text("Km/h")],
]
	
layout_rpm = [
	[sg.Text("0000",key="rpm",font=(None,100)),sg.Text("rpm")]
]	
#Tela Principal
layout = [
	[sg.Frame("Velocidade",layout = layout_vel),sg.Frame("RPM",layout = layout_rpm)],
	[sg.Text("COM:"),sg.Input(key="com"),sg.Button("Conectar")],
	[sg.Button("Iniciar teste"),sg.Button("Parar teste"),sg.Button("Novo teste")],
	[sg.Text("")]
]


   	
ExcelInit()

#Iniciar janela:
janela_principal = sg.Window("Telemetria",layout)

while conexao == False:
		event,values = janela_principal.read(timeout = 1000)
		if event == "Conectar":
			try:
				#ser = serial.Serial(f"COM{com}",9600,timeout=0.5)
				ser = serial.Serial(f"/dev/ttyACM0",9600,timeout=0.5)
				
				conexao = True
				sg.popup("Conexao feita com sucesso!")
			except Exception as e:
				print("Nao foi possivel se conectar a essa porta,por favor insira uma valida")
				print(f"Error: {e}")

start = False
while True:
	event,values = janela_principal.read(timeout=100)
		
	if start == True:
		print("recebendo")			
		RecebeDados()
	
	if event == "Iniciar teste":
		start = True
		print("teste iniciado")
		
	
	elif event == "Parar teste":
		start = False
		sg.popup("Teste concluido! Clique em novo teste para criar outra planilha para salvar os dados !")
	
	elif event == "Novo teste":
		teste = teste + 1
		ExcelInit(test = teste)
		sg.popup("Nova planilha feita!")
		
	elif event == None:
		wb.save("AceRet.xlsx")
		janela_principal.close()
		break
