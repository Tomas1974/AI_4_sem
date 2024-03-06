import { Injectable } from '@angular/core';
import {BaseDto,  ServerSendsIOTDataToClientsDto} from "./BaseDto";
import {temperaturModel} from "./tempModel";



@Injectable({
  providedIn: 'root'
})
export class DataService {

  secCounter:number=0;
  temperatureData: temperaturModel[]=[];

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

      let temp: temperaturModel;
      temp = {
        name: 'Sensor1',
        series: [{name: this.secCounter.toString(), value: parseFloat(dto.data)}]
      }



      this.temperatureData.push(temp);

      this.temperatureData=[...this.temperatureData];

    }

  }



    nulstil()
    {

      this.temperatureData=[...this.temperatureData];

    }

}

