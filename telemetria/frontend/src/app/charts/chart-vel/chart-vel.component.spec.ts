import { ComponentFixture, TestBed } from '@angular/core/testing';

import { ChartVelComponent } from './chart-vel.component';

describe('ChartVelComponent', () => {
  let component: ChartVelComponent;
  let fixture: ComponentFixture<ChartVelComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [ChartVelComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(ChartVelComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
