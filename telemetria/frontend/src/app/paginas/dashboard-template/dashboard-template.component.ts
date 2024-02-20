import { Component } from '@angular/core';
import { ChartVelComponent } from '../../charts/chart-vel/chart-vel.component';

@Component({
  selector: 'app-dashboard-template',
  standalone: true,
  imports: [ChartVelComponent],
  templateUrl: './dashboard-template.component.html',
  styleUrl: './dashboard-template.component.scss',
})
export class DashboardTemplateComponent {}
