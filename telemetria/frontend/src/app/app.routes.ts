import { Routes } from '@angular/router';
import { DashboardTemplateComponent } from './paginas/dashboard-template/dashboard-template.component';
import { NotFoundComponent } from './paginas/not-found/not-found.component';

export const routes: Routes = [
  { path: '', component: DashboardTemplateComponent },
  { path: '**', component: NotFoundComponent },
];
