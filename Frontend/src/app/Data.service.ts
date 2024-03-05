import { Injectable } from '@angular/core';
import {BaseDto, ClientWantsToGetAllFarverDto, ServerSendsIOTDataToClientsDto} from "./BaseDto";
import {temperaturModel} from "./farveModel";


@Injectable({
  providedIn: 'root'
})
export class DataService {

  secCounter:number=0;
  temperature: any[]=[
    {
      "name": "Temp1",
      "series": [
        {
          "name": "1",
          "value": 21
        },
        {
          "name": "2",
          "value": 22
        },
        {
          "name": "3",
          "value": 23
        }
      ]
    }];




  ws: WebSocket = new WebSocket("ws://localhost:8181")


  constructor() {
    this.ws.onmessage = message => {
      const messageFromServer = JSON.parse(message.data) as BaseDto<any>;
      // @ts-ignore
      this[messageFromServer.eventType].call(this, messageFromServer);
    }
  }


  ServerSendsIOTDataToClients(dto: ServerSendsIOTDataToClientsDto) {
    if (dto.data != null) {

      this.secCounter++;






    }

  }










  //   nulstil()
  //   {
  //     this.farve_count[0].value=0;
  //     this.farve_count[1].value=0;
  //     this.farve_count[2].value=0;
  //     this.farve_count=[...this.farve_count];
  //     this.farve_procent = [
  //
  //       { name: "Red", value: 0 },
  //       { name: "Yellow", value: 0},
  //       { name: "Green", value: 0 }
  //     ];
  //     this.farve_procent=[...this.farve_procent];
  //   }

}
