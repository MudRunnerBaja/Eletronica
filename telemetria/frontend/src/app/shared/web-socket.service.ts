import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import * as io from 'socket.io-client';


@Injectable({
  providedIn: 'root'
})
export class WebSocketService {

  socket:any;
  readonly url:string = "http://localhost:3000"

  constructor() { 
    this.socket = io.connect(this.url);
  }

  listen(evento:string):Observable<any>{
    return new Observable((subscribe)=>{
      this.socket.on(evento, (data:any)=>{
        subscribe.next(data)
      })
    })
  }


  emit(evento:string,data:any){
    this.socket.emit(evento, data)
  }
}
