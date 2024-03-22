import { Injectable } from '@angular/core';
import {BaseDto,  ServerSendsIOTDataToClientsDto} from "./BaseDto";
import {temperaturModel} from "./tempModel";



@Injectable({
  providedIn: 'root'
})
export class DataService {

  secCounter:number=0;
  temperatureData: temperaturModel[]=[];
  start: boolean=false;

  ws: WebSocket = new WebSocket("ws://localhost:8181")
  graphName: string="";

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
      const existingSeries = this.temperatureData.find(series => series.name === this.graphName);

        if (existingSeries) {
        existingSeries.series.push({
          name: this.secCounter.toString(),
          value: parseFloat(dto.data)
        });
      } else {
        const newSeries = {
          name: this.graphName,
          series: [{name: this.secCounter.toString(), value: parseFloat(dto.data)}]
        };
        this.temperatureData.push(newSeries); // Push the new series to temperatureData
      }

      // Ensure this line is inside the if/else block to apply changes
      this.temperatureData = [...this.temperatureData];

    }

  }


  startStop()
  {
    if (this.start)
      this.start=false;
    else
      this.start=true;

    var object = {
      eventType: "StartStop",
      start_stop: "Start"

    }
    this.ws.send(JSON.stringify(object));


  }



  nulstil()
    {

      this.temperatureData=[];

    }

}

