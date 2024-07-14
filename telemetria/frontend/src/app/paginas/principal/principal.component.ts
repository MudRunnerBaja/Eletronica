import { AfterViewInit, Component, ViewChild } from '@angular/core';
import { ChartRpmComponent } from '../../charts/chart-rpm/chart-rpm.component';
import { ChartVelComponent } from '../../charts/chart-vel/chart-vel.component';

@Component({
  selector: 'app-principal',
  standalone: true,
  imports: [ChartVelComponent, ChartRpmComponent],
  templateUrl: './principal.component.html',
  styleUrl: './principal.component.scss'
})
export class PrincipalComponent implements AfterViewInit {

  constructor() {

  }

  @ViewChild('chartRpm', { static: false }) chartRpm!: ChartRpmComponent;
  @ViewChild('chartVel', { static: false }) chartVel!: ChartVelComponent;

  public ultimaVel: number = 0;
  public ultimoRPM: number = 0;

  ngAfterViewInit(): void {
  }
  
  getUltimoRpm(rpm: any) {
    this.ultimoRPM = rpm;
  }

  getUltimaVel(vel: any) {
    this.ultimaVel = vel;
  }
}