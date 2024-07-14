import { CommonModule } from '@angular/common';
import { Component, ElementRef, ViewChild, AfterViewInit, Input, ChangeDetectorRef, Output, EventEmitter } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { Chart } from 'chart.js/auto';
import { Dados } from '../../models/dados';
import { WebSocketService } from '../../shared/web-socket.service';

@Component({
  selector: 'app-chart-rpm',
  standalone: true,
  imports: [CommonModule, RouterOutlet],
  templateUrl: './chart-rpm.component.html',
  styleUrl: './chart-rpm.component.scss',
})
export class ChartRpmComponent implements AfterViewInit {

  constructor(private WebSocketService: WebSocketService,
  ) {}

  @ViewChild('chartRef', { static: false }) chartElementRef!: ElementRef;
  @Output() ultimoDado = new EventEmitter<number>();

  public chartName: string = 'RPM';
  public conjunto: Dados[] = [];
  public count: number = 10;

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
            label: 'RPM',
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
      // console.log(data);
      let dataObj: Dados = JSON.parse(data);
      this.ultimoDado.emit(dataObj.rpm);

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
