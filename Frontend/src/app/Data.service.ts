import { Injectable } from '@angular/core';
import {BaseDto, ClientWantsToGetAllFarverDto, ServerSendsIOTDataToClientsDto} from "./BaseDto";
import {farveModel} from "./farveModel";


@Injectable({
  providedIn: 'root'
})
export class DataService {


  farve_count:farveModel[] = [
    { name: "Red", value: 0 },
    { name: "Yellow", value: 0 },
    { name: "Green", value: 0 }
  ];

  farve_procent:farveModel[] = [
    { name: "Red", value: 0 },
    { name: "Yellow", value: 0 },
    { name: "Green", value: 0 }
  ];


  ws: WebSocket = new WebSocket("ws://localhost:8181")


  constructor() {
    this.ws.onmessage = message => {
      const messageFromServer = JSON.parse(message.data) as BaseDto<any>;
      // @ts-ignore
      this[messageFromServer.eventType].call(this, messageFromServer);
    }
  }

  public RødProcent() : number
  {

    return this.farve_count[0].value/(this.farve_count[0].value+this.farve_count[1].value+this.farve_count[2].value)*100;
  }

  public GulProcent() : number
  {

    return this.farve_count[1].value/(this.farve_count[0].value+this.farve_count[1].value+this.farve_count[2].value)*100;
  }

  public GrønProcent() : number
  {

    return this.farve_count[2].value/(this.farve_count[0].value+this.farve_count[1].value+this.farve_count[2].value)*100;
  }


  ServerSendsIOTDataToClients(dto: ServerSendsIOTDataToClientsDto) {
    if (dto.data != null) {

      switch(dto.data) {
        case "RED":
          this.farve_count[0].value=this.farve_count[0].value+1;
          console.log("tilføjet rød");
          break;
        case "YELLOW":
          this.farve_count[1].value=this.farve_count[1].value+1;
          console.log("tilføjet gul");
          break;
        case "GREEN":
          console.log("tilføjet grøn");
          this.farve_count[2].value=this.farve_count[2].value+1;
          break;
      }

      this.farve_count=[...this.farve_count];

      this.farve_procent = [
        { name: "Red", value: this.RødProcent() },
        { name: "Yellow", value: this.GulProcent()},
        { name: "Green", value: this.GrønProcent() }
      ];
      this.farve_procent=[...this.farve_procent];
    }

  }

  TilføjFarve(dto: ClientWantsToGetAllFarverDto): void

  {
    try
    {

      // @ts-ignore
      for (let i = 0; i < dto.farver?.length; i++) {
        {
          // @ts-ignore
          switch(dto.farver[i]) {
            case "RED":
              this.farve_count[0].value=this.farve_count[0].value+1;
              break;
            case "YELLOW":
              this.farve_count[1].value=this.farve_count[1].value+1;
              break;
            case "GREEN":
              this.farve_count[2].value=this.farve_count[2].value+1;
              break;
          }
        }
      }
      this.farve_count=[...this.farve_count];


      this.farve_procent = [
        { name: "Red", value: this.RødProcent() },
        { name: "Yellow", value: this.GulProcent()},
        { name: "Green", value: this.GrønProcent() }
      ];
      this.farve_procent=[...this.farve_procent];

    }
    catch (e)
    {
      console.log(e)
    }
  }

    nulstil()
    {
      this.farve_count[0].value=0;
      this.farve_count[1].value=0;
      this.farve_count[2].value=0;
      this.farve_count=[...this.farve_count];
      this.farve_procent = [

        { name: "Red", value: 0 },
        { name: "Yellow", value: 0},
        { name: "Green", value: 0 }
      ];
      this.farve_procent=[...this.farve_procent];
    }

}
