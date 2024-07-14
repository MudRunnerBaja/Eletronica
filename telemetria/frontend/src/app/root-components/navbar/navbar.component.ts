import { Component } from '@angular/core';
import { NgbNavChangeEvent, NgbNavModule } from '@ng-bootstrap/ng-bootstrap';
import { PrincipalComponent } from '../../paginas/principal/principal.component';

@Component({
  selector: 'app-navbar',
  standalone: true,
  imports: [NgbNavModule, PrincipalComponent],
  templateUrl: './navbar.component.html',
  styleUrl: './navbar.component.scss',
})
export class NavbarComponent {
  public active: any;
	disabled = true;

  /*
  1 = Principal
  2 = Simplificado
  
  */

	onNavChange(changeEvent: NgbNavChangeEvent) {

	}

	toggleDisabled() {
		this.disabled = !this.disabled;
		if (this.disabled) {
			this.active = 1;
		}
	}

}
