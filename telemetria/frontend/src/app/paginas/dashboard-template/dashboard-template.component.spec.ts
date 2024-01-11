import { ComponentFixture, TestBed } from '@angular/core/testing';

import { DashboardTemplateComponent } from './dashboard-template.component';

describe('DashboardTemplateComponent', () => {
  let component: DashboardTemplateComponent;
  let fixture: ComponentFixture<DashboardTemplateComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [DashboardTemplateComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(DashboardTemplateComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
