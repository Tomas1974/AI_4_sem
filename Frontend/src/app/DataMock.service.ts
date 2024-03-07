import { Injectable } from '@angular/core';
import {BaseDto,  ServerSendsIOTDataToClientsDto} from "./BaseDto";
import {temperaturModel} from "./tempModel";



@Injectable({
  providedIn: 'root'
})
export class DataMockService {

  secCounter:number=3;

  temperatureData: temperaturModel[]=[
    {
      name: "Serie1",
      series: [
        {
          "name": "1",
          "value": 20
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
    }

  ];


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
        console.log(dto.data);
      const existingSeries = this.temperatureData.find(series => series.name === 'Serie1');

      if (existingSeries) {
        existingSeries.series.push({
          name: this.secCounter.toString(),
          value: parseFloat(dto.data)
        });
      } else {
        // If for some reason the series does not exist, create it and push to temperatureData
        const newSeries = {
          name: 'Serie1',
          series: [{name: this.secCounter.toString(), value: parseFloat(dto.data)}]
        };
        this.temperatureData.push(newSeries); // Push the new series to temperatureData
      }

      // Ensure this line is inside the if/else block to apply changes
      this.temperatureData = [...this.temperatureData];

    }

  }



    nulstil()
    {

      this.temperatureData=[...this.temperatureData];

    }

}

