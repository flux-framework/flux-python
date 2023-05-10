#!/usr/bin/env python3

import flux
import flux.job

jobspec = flux.job.JobspecV1.from_command(["echo", "hello", "bacon", "pancakes!"])
future = flux.job.submit_async(flux.Flux(), jobspec)
print("Submit job %s" % future)
