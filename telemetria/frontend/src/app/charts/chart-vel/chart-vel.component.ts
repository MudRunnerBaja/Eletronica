import { CommonModule } from '@angular/common';
import { Component, ElementRef, ViewChild, AfterViewInit } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { Chart } from 'chart.js/auto';
import { Dados } from '../../models/dados';
import { WebSocketService } from '../../shared/web-socket.service';

@Component({
  selector: 'app-chart-vel',
  standalone: true,
  imports: [CommonModule, RouterOutlet],
  templateUrl: './chart-vel.component.html',
  styleUrl: './chart-vel.component.scss',
})
export class ChartVelComponent implements AfterViewInit {
  @ViewChild('chartRef', { static: true }) chartElementRef!: ElementRef;

  public conjunto: Dados[] = [];
  public count: number = 10;

  constructor(private WebSocketService: WebSocketService) {}

  ngAfterViewInit(): void {
    this.init();
  }

  init(): void {
    console.log(this.chartElementRef);
    console.log(this.chartElementRef.nativeElement);

    let chart: Chart = new Chart(this.chartElementRef.nativeElement, {
      type: 'line',
      data: {
        labels: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        datasets: [
          {
            label: 'rpm',
            data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
          },
        ],
      },
    });
    console.log(chart);

    this.WebSocketService.emit('mensagemDoCliente', 'Olá, servidor!');

    this.WebSocketService.listen('mensagemDoServidor').subscribe((data) => {
      console.log(data);
    });

    this.WebSocketService.listen('dataArduino').subscribe((data) => {
      console.log(data);
      let dataObj: Dados = JSON.parse(data);
      this.conjunto.push(dataObj);
      //aumenta o contador de interações
      this.count += 1;
      //atualiza o chart
      //lables
      chart.data.labels!.shift();
      chart.data.labels!.push(this.count - 10);

      //informações
      chart.data.datasets.forEach((dataset) => {
        dataset.data.shift();
      });
      chart.data.datasets.forEach((dataset) => {
        dataset.data.push(this.conjunto[this.count - 11].rpm);
      });

      chart.update('none');
    });
  }
}
